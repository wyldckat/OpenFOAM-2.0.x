/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "noThermo.H"
#include "addToRunTimeSelectionTable.H"
#include "volFields.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace regionModels
{
namespace thermoBaffleModels
{

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

defineTypeNameAndDebug(noThermo, 0);
addToRunTimeSelectionTable(thermoBaffleModel, noThermo, mesh);
addToRunTimeSelectionTable(thermoBaffleModel, noThermo, dictionary);

// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

bool noThermo::read()
{
    return regionModel1D::read();
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

noThermo::noThermo(const word& modelType, const fvMesh& mesh)
:
    thermoBaffleModel(mesh)
{}


noThermo::noThermo
(
    const word& modelType,
    const fvMesh& mesh,
    const dictionary& dict
)
:
    thermoBaffleModel(mesh)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

noThermo::~noThermo()
{}

// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

void noThermo::preEvolveRegion()
{}


void noThermo::evolveRegion()
{}


const tmp<volScalarField> noThermo::Cp() const
{
    FatalErrorIn("const tmp<volScalarField>& noThermo::Cp() const")
        << "Cp field not available for " << type() << abort(FatalError);

    return tmp<volScalarField>
    (
        new volScalarField
        (
            IOobject
            (
                "noThermo::Cp",
                time().timeName(),
                primaryMesh(),
                IOobject::NO_READ,
                IOobject::NO_WRITE,
                false
            ),
            primaryMesh(),
            dimensionedScalar("zero", dimEnergy/dimVolume/dimTime, 0.0)
        )
    );
}

const volScalarField& noThermo::kappa() const
{
    FatalErrorIn("const volScalarField& noThermo::kappa() const")
        << "kappa field not available for " << type() << abort(FatalError);
    return volScalarField::null();
}


const volScalarField& noThermo::rho() const
{
    FatalErrorIn("const volScalarField& noThermo::rho() const")
        << "rho field not available for " << type() << abort(FatalError);
    return volScalarField::null();
}


const volScalarField& noThermo::K() const
{
   FatalErrorIn("const volScalarField& noThermo::K() const")
        << "K field not available for " << type() << abort(FatalError);
    return volScalarField::null();
}


const volScalarField& noThermo::T() const
{
    FatalErrorIn("const volScalarField& noThermo::T() const")
        << "T field not available for " << type() << abort(FatalError);
    return volScalarField::null();
}


const basicSolidThermo& noThermo::thermo() const
{
    FatalErrorIn("const volScalarField& noThermo::T() const")
        << "T field not available for " << type() << abort(FatalError);
    return reinterpret_cast<const basicSolidThermo&>(null);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace thermoBaffleModels
} // End namespace regionModels
} // End namespace Foam

// ************************************************************************* //
