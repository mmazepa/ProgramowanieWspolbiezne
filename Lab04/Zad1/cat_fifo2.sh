#!/bin/bash
echo "Napisz coś:"
cat > fifo2 | cat > fifo1
