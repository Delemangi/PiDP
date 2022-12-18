#!/usr/bin/env python

import sys
import re

for line in sys.stdin:
    line = line.strip()
    match = re.search(r'(\S+).+\[.+/(.+)/.+\] \"\S+ (.+) HTTP.*" \S+ \S+', line)
    ip = match.group(1)
    month = match.group(2)
    file_ = match.group(3)
    print '%s %s [%s]' % (month, file_, ip)
