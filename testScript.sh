#!/usr/bin/env bash

# Start the first process in the background and save its PID
echo "s" | ./build/TrashFight &
PID1=$!

# Start the second process in the background and save its PID
echo "c" | ./build/TrashFight &
PID2=$!

# Define cleanup function
cleanup() {
    kill $PID1 $PID2
    clear
    exit 0
}

# Trap Ctrl+C (SIGINT) and normal exit (EXIT)
trap cleanup SIGINT EXIT

while true; do
    sleep 1  # Keep script alive (no busy-waiting)
done



