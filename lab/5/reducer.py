#!/usr/bin/env python

import sys
import re

current_month_file = None
current_ips = []
word = None

for line in sys.stdin:
    line = line.strip()

    match = re.search(r'(\S+) (.+) \[(\S+)\]', line)
    month = match.group(1)
    file_ = match.group(2)
    ip = match.group(3)
    month_file = '%s %s' % (month, file_)

    if current_month_file == month_file:
        current_ips.append(ip)
    else:
        if current_month_file:
            print '%s [%s]' % (current_month_file,  ' '.join(current_ips))
        current_ips = []
        current_month_file = month_file

if current_month_file:
    print '%s [%s]' % (current_month_file, ' '.join(current_ips))
