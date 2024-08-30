#!/bin/bash
#
# The MIT License (MIT)
#
# Copyright (c) 2024-2025 Kris Jusiak <kris@jusiak.net>
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
SAMPLE_RATE=""
RPMC_ENABLED=false
SET_PERF=false
PERF_DEBUG_MODE=755
PERF_TRACING_MODE=755

usage() {
  echo "Usage: $0 [options]"
  echo ""
  echo "Options:"
  echo "  -p, --perf                 Enable perf setup: sysctls, remount debugfs, set uprobe_events [default: not set]"
  echo "  -r, --rdpmc                Enable rdpmc (sets value to 2) [default: not set]"
  echo "  -s, --sample-rate RATE     Set perf_event_max_sample_rate (e.g., 100000) [default: not set]"
  echo "  -h, --help                 Show this help message"
  echo ""
  echo "Usage:"
  echo "  $0"
  echo "    Run with defaults (perf setup enabled, rdpmc off, no sample rate)"
  exit 1
}

while [[ "$#" -gt 0 ]]; do
  case $1 in
    -p|--perf) SET_PERF=true ;;
    -r|--rdpmc) RPMC_ENABLED=true ;;
    -s|--sample-rate) SAMPLE_RATE="$2"; shift ;;
    -h|--help) usage ;;
    *) echo "Unknown parameter: $1"; usage ;;
  esac
  shift
done

if [[ -z "$SAMPLE_RATE" && "$RPMC_ENABLED" == false && "$SET_PERF" == false ]]; then
  usage
fi

if $SET_PERF; then
  sudo mount -o remount,mode=$PERF_DEBUG_MODE /sys/kernel/debug
  sudo mount -o remount,mode=$PERF_TRACING_MODE /sys/kernel/debug/tracing
  echo 0 | sudo tee /proc/sys/kernel/kptr_restrict
  echo -1 | sudo tee /proc/sys/kernel/perf_event_paranoid
  sudo chown "$(whoami)" /sys/kernel/debug/tracing/uprobe_events
  sudo chmod a+rw /sys/kernel/debug/tracing/uprobe_events
fi

if [[ -n "$SAMPLE_RATE" ]]; then
  echo "$SAMPLE_RATE" | sudo tee /proc/sys/kernel/perf_event_max_sample_rate
fi

if $RPMC_ENABLED; then
  echo 2 | sudo tee /sys/devices/cpu_core/rdpmc
fi
