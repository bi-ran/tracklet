#!/bin/bash

if [[ $# -ne 1 ]]; then
    echo -e "usage: ./processpixel.sh [list]\n"
    exit 1
fi

mkdir -p /export/d00/scratch/biran/tracklet/$1

cat $1 | while read LINE; do
    TAG=${LINE##*/}
    TAG=${TAG%%.*}
    cat refineraw.py | sed "s:___C___:$LINE:g" | sed "s:___D___:$TAG:g" | sed "s:___E___:$1:g" > log/refine_$TAG.py
    cmsRun log/refine_$TAG.py &> log/refine_$TAG.log
done
