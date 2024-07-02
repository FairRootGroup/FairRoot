#! /bin/bash

if [ $# -lt 4 ]
then
	echo "*** Please call like: $0 LABEL CONTAINER JOBSH CTEST [CTESTARG ...]"
	exit 1
fi

label="$1"; shift
container="$1"; shift
jobsh="$1"; shift
# Convert commandline array into single string, with proper quoting
ctestcmd="$(printf ' %q' "$@")"
# Strip leading space
ctestcmd="${ctestcmd:1}"

echo "*** Creating job script ..: ${jobsh}"

(
	echo   '# #! /bin/bash'
	echo   "# export LABEL=${label}"
	echo   '  echo "*** Job started at .......: $(date -R)"'
	echo   '  echo "*** Job ID ...............: $SLURM_JOB_ID"'
	echo   '  echo "*** Compute node .........: $(hostname -f)"'
	echo   "# source <(sed -e '/^#/d' -e '/^export/!s/^.*=/export &/' /etc/environment)"
	printf '# ./test/test-start-container.sh %q %q\n' "${container}" "${ctestcmd}"
	echo   '# retval=$?'
	echo   '# mkdir -p build'
	echo   '# echo $retval >"build/${LABEL}-last-exit-code"'
	echo   '# exit $retval'
	echo   'newhomedir="$(mktemp --tmpdir -d FairRoot-CI-home.XXXXXX)"'
	echo   '  echo "*** Temporary homedir ....: $newhomedir"'
	echo   '  unset http_proxy'
	echo   '  unset HTTP_PROXY'
	printf 'singularity exec --writable-tmpfs -B/shared -H "${newhomedir}" %q bash -l -c %q\n' \
		"${SINGULARITY_CONTAINER_ROOT}/fairroot/${container}" \
		"${ctestcmd}"
) >> "$jobsh"

echo "*** Content:"
sed -e 's/^/    /' "$jobsh"
