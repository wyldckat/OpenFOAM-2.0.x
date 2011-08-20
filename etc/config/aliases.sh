#----------------------------------*-sh-*--------------------------------------
# =========                 |
# \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
#  \\    /   O peration     |
#   \\  /    A nd           | Copyright (C) 2011 OpenFOAM Foundation
#    \\/     M anipulation  |
#------------------------------------------------------------------------------
# License
#     This file is part of OpenFOAM.
#
#     OpenFOAM is free software: you can redistribute it and/or modify it
#     under the terms of the GNU General Public License as published by
#     the Free Software Foundation, either version 3 of the License, or
#     (at your option) any later version.
#
#     OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
#     ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
#     FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
#     for more details.
#
#     You should have received a copy of the GNU General Public License
#     along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.
#
# File
#     etc/config/aliases.sh
#
# Description
#     Aliases for working with OpenFOAM
#     Sourced from OpenFOAM-<VERSION>/etc/bashrc and/or ~/.bashrc
#
#------------------------------------------------------------------------------

# Change compiled version aliases
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
alias wmSET='. $WM_PROJECT_DIR/etc/bashrc'
alias wm64='wmSET WM_ARCH_OPTION=64'
alias wm32='wmSET WM_ARCH_OPTION=32'
alias wmSP='wmSET WM_PRECISION_OPTION=SP'
alias wmDP='wmSET WM_PRECISION_OPTION=DP'

# clear env
alias wmUNSET='. $WM_PROJECT_DIR/etc/config/unset.sh'

# Toggle wmakeScheduler on/off
#  - also need to set WM_HOSTS
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
alias wmSchedON='export WM_SCHEDULER=$WM_PROJECT_DIR/wmake/wmakeScheduler'
alias wmSchedOFF='unset WM_SCHEDULER'

# Set hosts for scheduler
#  - if none defined, single machine is assumed by wmakeScheduler
wmHosts()
{
    export WM_HOSTS="$*"
}

# Set default colours for scheduler
alias wmColours='black blue green cyan red magenta yellow'

# Fast switching between multi-core and single-core building
#   wmSCS - single-core single-machine
#   wmMCS - multi-core single-machine
#   wmMCM - multi-core multi-machine
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
alias wmSCS='unset WM_NCOMPPROCS && echo "Building enabled for a single core"'
alias wmMCS='export WM_NCOMPPROCS=1; test -r /proc/cpuinfo && export WM_NCOMPPROCS=$(egrep "^processor" /proc/cpuinfo | wc -l) && echo "Building enabled for $WM_NCOMPPROCS cores"'
alias wmMCM='export WM_NCOMPPROCS=$(wmSchedON; $WM_SCHEDULER -count) && echo "Building enabled for $WM_NCOMPPROCS core(s)"'

# Change ParaView version
# ~~~~~~~~~~~~~~~~~~~~~~~
unset foamPV
foamPV()
{
    . $WM_PROJECT_DIR/etc/config/paraview.sh ParaView_VERSION=$1
    echo "paraview-$ParaView_VERSION  (major: $ParaView_MAJOR)"
}


# Change directory aliases
# ~~~~~~~~~~~~~~~~~~~~~~~~
alias src='cd $FOAM_SRC'
alias lib='cd $FOAM_LIBBIN'
alias run='cd $FOAM_RUN'
alias foam='cd $WM_PROJECT_DIR'
alias foamsrc='cd $FOAM_SRC/$WM_PROJECT'
alias foamfv='cd $FOAM_SRC/finiteVolume'
alias app='cd $FOAM_APP'
alias util='cd $FOAM_UTILITIES'
alias sol='cd $FOAM_SOLVERS'
alias tut='cd $FOAM_TUTORIALS'

alias foamApps='cd $FOAM_APP'
alias foamSol='cd $FOAM_SOLVERS'
alias foamTuts='cd $FOAM_TUTORIALS'
alias foamUtils='cd $FOAM_UTILITIES'
alias foam3rdParty='cd $WM_THIRD_PARTY_DIR'

if [ -n "$WM_PROJECT_SITE" ]
then
    alias foamSite='cd $WM_PROJECT_SITE'
else
    alias foamSite='cd $WM_PROJECT_INST_DIR/site'
fi

# -----------------------------------------------------------------------------
