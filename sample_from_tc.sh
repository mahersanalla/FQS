
#!/bin/bash
#tc -s qdisc show dev s2-eth2 | tail -n 1 | cut -d' ' -f4 | rev | cut -c2- | rev & sleep 5 ; kill $!
./.recursive_sampler_endless_loop.sh & sleep 180 ; kill $!
