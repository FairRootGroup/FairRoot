#! /bin/bash

if [ $# != 2 ]
then
	echo "*** Please call like: $0 LABEL JOBSH"
	exit 1
fi

label="$1"
jobsh="$2"

if [ -z "$ALFACI_SLURM_CPUS" ]
then
	# ALFACI_SLURM_CPUS=20
	:
fi
if [ -z "$ALFACI_SLURM_EXTRA_OPTS" ]
then
	ALFACI_SLURM_EXTRA_OPTS="--exclusive --cpu-bind=no"
fi
if [ -z "$ALFACI_SLURM_TIMEOUT" ]
then
	ALFACI_SLURM_TIMEOUT=30
fi
if [ -z "$ALFACI_SLURM_QUEUE" ]
then
	ALFACI_SLURM_QUEUE=main
fi
case "${label}" in
	*check/*)
		slurm_requested_features=localworkspace
		;;
esac

echo "*** Slurm request options :"
echo "***   Working directory ..: $PWD"
echo "***   Queue ..............: $ALFACI_SLURM_QUEUE"
if [ -n "$ALFACI_SLURM_CPUS" ]
then
	echo "***   CPUs ...............: $ALFACI_SLURM_CPUS"
fi
echo "***   Wall Time ..........: $ALFACI_SLURM_TIMEOUT min"
echo "***   Job Name ...........: ${label}"
echo "***   Extra Options ......: ${ALFACI_SLURM_EXTRA_OPTS}"
if [ -n "$slurm_requested_features" ]
then
	echo "***   Requested Features .: $slurm_requested_features"
fi

srun_cmdline_opts="-p $ALFACI_SLURM_QUEUE -n 1 -N 1 -t $ALFACI_SLURM_TIMEOUT"
if [ -n "$ALFACI_SLURM_CPUS" ]
then
	srun_cmdline_opts="$srun_cmdline_opts -c $ALFACI_SLURM_CPUS"
fi
if [ -n "$slurm_requested_features" ]
then
	srun_cmdline_opts="$srun_cmdline_opts --constraint=$slurm_requested_features"
fi

echo "*** Submitting job at ....: $(date -R)"
(
	set -x
	srun $srun_cmdline_opts \
		--job-name="${label}" \
		${ALFACI_SLURM_EXTRA_OPTS} \
		bash "${jobsh}"
)
retval=$?
echo "*** Exit Code ............: $retval"
exit "$retval"
