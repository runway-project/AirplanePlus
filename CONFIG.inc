source ../CONFIG.inc

PACKAGE="AirplanePlus"
TARGETDIR="${PACKAGE}"
TARGETBINDIR="$TARGETDIR/Plugins"
PROJECTSDIR="Source/$PACKAGE/"
VERSIONFILE="$PACKAGE.version"

DLLS="$PACKAGE"
# PluginData DLLs
PD_DLLS=""
# Rule oriented deployoment for PluginData
#declare -A PD_SUB_RULES=( ["KSPe.UI.12"]="./12x/KSPe.UI" ["KSPe.UI.14"]="./14x/KSPe.UI" ["KSPe.UI.18"]="./18x/KSPe.UI" )
declare -A PD_SUB_RULES=( )
PD_SUB_DLLS=`{ for K in "${!PD_SUB_RULES[@]}"; do echo $(basename ${PD_SUB_RULES[$K]}); done } | sort -u | tr '\n' ' '`
PD_SUB_DIRS=`{ for K in "${!PD_SUB_RULES[@]}"; do echo $(dirname ${PD_SUB_RULES[$K]}); done } | sort -u | tr '\n' ' '`

# GameData deployed DLLs
GD_DLLS="KSPe"
GD_PRIORITY="000"

# Dev LIB deployed DLLs
LIB_DLLS="${DLLS}"

# External Libs from the LIB directory
EXT_DLLS=""


PROJECT_BRANCH=`git branch | grep \* | cut -d ' ' -f2`
if [ "$PROJECT_BRANCH" == "master" ] ; then
	# Release mode
	PROJECT_STATE="-BETA"
else
	# Note: Add a leading dash when this value is present!
	PROJECT_STATE="-BETA"
fi

VERSION=$( cat $VERSIONFILE | tr '\n' ' ' | sed -n -E 's/^.*?"VERSION\":\{.*"MAJOR":([0-9]+?),.*?"MINOR":([0-9]+?),.*?"PATCH":([0-9]+?),.*?"BUILD":([0-9]+?).*?\}.*$/\1.\2.\3.\4/p' )
