#!/bin/bash
echo ""
echo "Zgodziłeś się na nasłuch."
echo "Ktoś z drugiej strony może napisać..."
echo ""
cat < fifo1 | cat < fifo2 &
