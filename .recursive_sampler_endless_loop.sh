#!/bin/bash

while true; do
tc -s qdisc show dev router-server | tail -n 1 | cut -d' ' -f4 | rev | cut -c2- | rev  >> tc_log.txt
done
