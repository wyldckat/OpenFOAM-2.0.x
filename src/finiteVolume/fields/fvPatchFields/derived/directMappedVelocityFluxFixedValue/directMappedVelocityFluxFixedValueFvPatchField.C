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

#include "directMappedVelocityFluxFixedValueFvPatchField.H"
#include "fvPatchFieldMapper.H"
#include "directMappedPatchBase.H"
#include "volFields.H"
#include "surfaceFields.H"
#include "addToRunTimeSelectionTable.H"


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::directMappedVelocityFluxFixedValueFvPatchField::
directMappedVelocityFluxFixedValueFvPatchField
(
    const fvPatch& p,
    const DimensionedField<vector, volMesh>& iF
)
:
    fixedValueFvPatchVectorField(p, iF),
    phiName_("phi")
{}


Foam::directMappedVelocityFluxFixedValueFvPatchField::
directMappedVelocityFluxFixedValueFvPatchField
(
    const directMappedVelocityFluxFixedValueFvPatchField& ptf,
    const fvPatch& p,
    const DimensionedField<vector, volMesh>& iF,
    const fvPatchFieldMapper& mapper
)
:
    fixedValueFvPatchVectorField(ptf, p, iF, mapper),
    phiName_(ptf.phiName_)
{
    if (!isA<directMappedPatchBase>(this->patch().patch()))
    {
        FatalErrorIn
        (
            "directMappedVelocityFluxFixedValueFvPatchField::"
            "directMappedVelocityFluxFixedValueFvPatchField"
            "("
                "const directMappedVelocityFluxFixedValueFvPatchField&, "
                "const fvPatch&, "
                "const DimensionedField<vector, volMesh>&, "
                "const fvPatchFieldMapper&"
            ")"
        )   << "Patch type '" << p.type()
            << "' not type '" << directMappedPatchBase::typeName << "'"
            << " for patch " << p.name()
            << " of field " << dimensionedInternalField().name()
            << " in file " << dimensionedInternalField().objectPath()
            << exit(FatalError);
    }
}


Foam::directMappedVelocityFluxFixedValueFvPatchField::
directMappedVelocityFluxFixedValueFvPatchField
(
    const fvPatch& p,
    const DimensionedField<vector, volMesh>& iF,
    const dictionary& dict
)
:
    fixedValueFvPatchVectorField(p, iF, dict),
    phiName_(dict.lookupOrDefault<word>("phi", "phi"))
{
    if (!isA<directMappedPatchBase>(this->patch().patch()))
    {
        FatalErrorIn
        (
            "directMappedVelocityFluxFixedValueFvPatchField::"
            "directMappedVelocityFluxFixedValueFvPatchField"
            "("
                "const fvPatch&, "
                "const DimensionedField<vector, volMesh>&, "
                "const dictionary&"
            ")"
        )   << "Patch type '" << p.type()
            << "' not type '" << directMappedPatchBase::typeName << "'"
            << " for patch " << p.name()
            << " of field " << dimensionedInternalField().name()
            << " in file " << dimensionedInternalField().objectPath()
            << exit(FatalError);
    }

    const directMappedPatchBase& mpp = refCast<const directMappedPatchBase>
    (
        this->patch().patch()
    );
    if (mpp.mode() == directMappedPolyPatch::NEARESTCELL)
    {
        FatalErrorIn
        (
            "directMappedVelocityFluxFixedValueFvPatchField::"
            "directMappedVelocityFluxFixedValueFvPatchField"
            "("
                "const fvPatch&, "
                "const DimensionedField<vector, volMesh>&, "
                "const dictionary&"
            ")"
        )   << "Patch " << p.name()
            << " of type '" << p.type()
            << "' can not be used in 'nearestCell' mode"
            << " of field " << dimensionedInternalField().name()
            << " in file " << dimensionedInternalField().objectPath()
            << exit(FatalError);
    }
}


Foam::directMappedVelocityFluxFixedValueFvPatchField::
directMappedVelocityFluxFixedValueFvPatchField
(
    const directMappedVelocityFluxFixedValueFvPatchField& ptf
)
:
    fixedValueFvPatchVectorField(ptf),
    phiName_(ptf.phiName_)
{}


Foam::directMappedVelocityFluxFixedValueFvPatchField::
directMappedVelocityFluxFixedValueFvPatchField
(
    const directMappedVelocityFluxFixedValueFvPatchField& ptf,
    const DimensionedField<vector, volMesh>& iF
)
:
    fixedValueFvPatchVectorField(ptf, iF),
    phiName_(ptf.phiName_)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void Foam::directMappedVelocityFluxFixedValueFvPatchField::updateCoeffs()
{
    if (updated())
    {
        return;
    }

    // Since we're inside initEvaluate/evaluate there might be processor
    // comms underway. Change the tag we use.
    int oldTag = UPstream::msgType();
    UPstream::msgType() = oldTag+1;

    // Get the directMappedPatchBase
    const directMappedPatchBase& mpp = refCast<const directMappedPatchBase>
    (
        directMappedVelocityFluxFixedValueFvPatchField::patch().patch()
    );
    const mapDistribute& distMap = mpp.map();
    const fvMesh& nbrMesh = refCast<const fvMesh>(mpp.sampleMesh());
    const word& fieldName = dimensionedInternalField().name();
    const volVectorField& UField = nbrMesh.lookupObject<volVectorField>
    (
        fieldName
    );

    surfaceScalarField& phiField = const_cast<surfaceScalarField&>
    (
        nbrMesh.lookupObject<surfaceScalarField>(phiName_)
    );

    vectorField newUValues;
    scalarField newPhiValues;

    switch (mpp.mode())
    {
        case directMappedPolyPatch::NEARESTFACE:
        {
            vectorField allUValues(nbrMesh.nFaces(), vector::zero);
            scalarField allPhiValues(nbrMesh.nFaces(), 0.0);

            forAll(UField.boundaryField(), patchI)
            {
                const fvPatchVectorField& Upf = UField.boundaryField()[patchI];
                const scalarField& phipf = phiField.boundaryField()[patchI];

                label faceStart = Upf.patch().start();

                forAll(Upf, faceI)
                {
                    allUValues[faceStart + faceI] = Upf[faceI];
                    allPhiValues[faceStart + faceI] = phipf[faceI];
                }
            }

            distMap.distribute(allUValues);
            newUValues.transfer(allUValues);

            distMap.distribute(allPhiValues);
            newPhiValues.transfer(allPhiValues);

            break;
        }
        case directMappedPolyPatch::NEARESTPATCHFACE:
        {
            const label nbrPatchID = nbrMesh.boundaryMesh().findPatchID
            (
                mpp.samplePatch()
            );

            newUValues = UField.boundaryField()[nbrPatchID];
            distMap.distribute(newUValues);

            newPhiValues = phiField.boundaryField()[nbrPatchID];
            distMap.distribute(newPhiValues);

            break;
        }
        default:
        {
            FatalErrorIn
            (
                "directMappedVelocityFluxFixedValueFvPatchField::"
                "updateCoeffs()"
            )   << "patch can only be used in NEARESTPATCHFACE or NEARESTFACE "
                << "mode" << nl << abort(FatalError);
        }
    }

    operator==(newUValues);
    phiField.boundaryField()[patch().index()] == newPhiValues;

    // Restore tag
    UPstream::msgType() = oldTag;

    fixedValueFvPatchVectorField::updateCoeffs();
}


void Foam::directMappedVelocityFluxFixedValueFvPatchField::write
(
    Ostream& os
) const
{
    fvPatchVectorField::write(os);
    writeEntryIfDifferent<word>(os, "phi", "phi", phiName_);
    this->writeEntry("value", os);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
    makePatchTypeField
    (
        fvPatchVectorField,
        directMappedVelocityFluxFixedValueFvPatchField
    );
}


// ************************************************************************* //
