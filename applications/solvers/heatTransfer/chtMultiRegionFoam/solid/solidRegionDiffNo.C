/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | foam-extend: Open Source CFD
   \\    /   O peration     |
    \\  /    A nd           | For copyright notice see file Copyright
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of foam-extend.

    foam-extend is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation, either version 3 of the License, or (at your
    option) any later version.

    foam-extend is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with foam-extend.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "solidRegionDiffNo.H"
#include "fvc.H"

Foam::scalar Foam::solidRegionDiffNo
(
    const fvMesh& mesh,
    const Time& runTime,
    const volScalarField& Cprho,
    const volScalarField& K
)
{
    scalar DiNum = 0.0;
    scalar meanDiNum = 0.0;

    //- Can have fluid domains with 0 cells so do not test.
    if (mesh.nInternalFaces())
    {
        surfaceScalarField KrhoCpbyDelta =
            mesh.surfaceInterpolation::deltaCoeffs()
          * fvc::interpolate(K)
          / fvc::interpolate(Cprho);

        DiNum = max(KrhoCpbyDelta.internalField())*runTime.deltaT().value();

        meanDiNum = (average(KrhoCpbyDelta)).value()*runTime.deltaT().value();
    }

    Info<< "Region: " << mesh.name() << " Diffusion Number mean: " << meanDiNum
        << " max: " << DiNum << endl;

    return DiNum;
}


// ************************************************************************* //
