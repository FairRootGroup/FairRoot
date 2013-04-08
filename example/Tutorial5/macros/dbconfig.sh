# add for MySql libs
# MAc OSx
export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:/usr/local/mysql/lib
# Linux
#export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/mysql/lib

# Local MySQL server
export ENV_TSQL_URL="mysql://localhost/r3b"
export ENV_TSQL_USER="scott"
export ENV_TSQL_PSWD="tiger"

# Local PgSQL server
#export ENV_TSQL_URL="pgsql://localhost:5432/R3B"
#export ENV_TSQL_USER="postgres"
#export ENV_TSQL_PSWD="pasglop1"
