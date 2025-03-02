#!/bin/bash

MAPS_DIR="./maps/invalid"
EXECUTABLE="./cub3D"  # Change this to your actual executable

if [ ! -f "$EXECUTABLE" ]; then
    echo "Error: Executable '$EXECUTABLE' not found. Please build it first."
    exit 1
fi

all_failed=true

for map in "$MAPS_DIR"/*; do
    if [ -f "$map" ]; then
        echo "Testing: $map"
        
        # Run the program with valgrind and capture the output
        output=$(valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=1 $EXECUTABLE "$map" 2>&1)
        valgrind_status=$?
        
        # Print full valgrind output
        echo "$output"

        # Check for memory leaks in the output
        if [[ "$output" == *"All heap blocks were freed"* ]]; then
            # If there are no leaks detected, this is considered a success
            echo "✔ No memory leaks detected."
        elif [ $valgrind_status -eq 1 ]; then
            # If valgrind returns 1 (indicating leaks), report them
            echo "✘ Memory leaks detected!"
            all_failed=false
        else
            # Check if the program is stuck in a loop (like before)
            pid=$!
            sleep 2  # Give the program some time to produce an output

            if ps -p $pid > /dev/null; then
                echo "✘ Program is stuck in a loop! Terminating..."
                kill -INT $pid  # Send SIGINT (Ctrl+C)
                all_failed=false
            else
                # Check if output contains "Error"
                if echo "$output" | grep -q "Error"; then
                    echo "✔ Error detected as expected."
                    echo "Error message:"
                    echo "$output"
                else
                    echo "✘ No error detected! Unexpected behavior."
                    all_failed=false
                fi
            fi
        fi
        echo "--------------------------------"
    fi
done

# Final summary
if $all_failed; then
    echo "All invalid maps correctly returned an error. ✅"
else
    echo "Some invalid maps did not return an error or memory leaks were detected! ❌"
    exit 1
fi
