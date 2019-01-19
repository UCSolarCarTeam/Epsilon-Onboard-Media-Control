#!/usr/bin/env bash
export AWS_ACCESS_KEY_ID=AKIAJ4M34KXJBKZK4L5A
export AWS_SECRET_ACCESS_KEY=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
export AWS_DEFAULT_REGION=us-west-2
export AWS_DEFAULT_OUTPUT=text

readarray -t song <<< "$(aws s3 ls s3://ucsolarteam.onboardmedia.songs | awk '{for (i=4; i<NF; i++) printf $i " "; print $NF}' | sed s/\ /\+/g | rev | cut -c 5- | rev )"

printf '%s\n' "${song[@]}"
echo ${#song[@]}
