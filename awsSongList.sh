#!/usr/bin/env bash
export AWS_DEFAULT_REGION=us-west-2
export AWS_DEFAULT_OUTPUT=text

readarray -t song <<< "$(aws s3 ls s3://ucsolarteam.onboardmedia.songs | awk '{for (i=4; i<NF; i++) printf $i " "; print $NF}' | sed s/\ /\+/g | rev | cut -c 5- | rev )"

printf '%s\n' "${song[@]}"
echo ${#song[@]}
