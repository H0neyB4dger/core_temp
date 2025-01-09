#!/bin/bash
sensors | grep Tctl | grep -o '[[:digit:]]\{1,3\}\.[[:digit:]]'