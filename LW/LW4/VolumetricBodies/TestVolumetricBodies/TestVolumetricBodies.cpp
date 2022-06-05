#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include <iostream>
#include <string>
#include "../VolumetricBodies/CBody.h"
#include "../VolumetricBodies/CSphere.h"
#include "../VolumetricBodies/CCone.h"
#include "../VolumetricBodies/CCylinder.h"
#include "../VolumetricBodies/CParallelepiped.h"
#include "../VolumetricBodies/CCompound.h"
#include "../VolumetricBodies/VolumetricSpace.h"

SCENARIO("Create bodies and gett their parameters") {

    GIVEN("CBodies") {

        CSphere sphere(45.21, 4.92);
        CCone cone(25.39, 2.09, 2.57);
        CCylinder cylinder(18.47, 0.69, 10.87);
        CParallelepiped parallelepiped(77.85, 26.87, 1.59, 2.47);
        CCompound compound;

        THEN("get sphere") 
        {
            CHECK(sphere.GetName() == "Sphere");
            CHECK(sphere.GetDensity() == 45.21);
            CHECK(sphere.GetRadius() == 4.92);
            CHECK(sphere.GetVolume() == Approx(498.87).margin(0.01));
            CHECK(sphere.GetMass() == Approx(22553.73).margin(0.01));
            CHECK(sphere.ToString() == "Sphere\nDensity: 45.21\nVolume: 498.87\nMass: 22553.73\nRadius: 4.92\n");
        }
        AND_THEN("get cone")
        {
            CHECK(cone.GetName() == "Cone");
            CHECK(cone.GetDensity() == 25.39);
            CHECK(cone.GetBaseRadius() == 2.09);
            CHECK(cone.GetHeight() == 2.57);
            CHECK(cone.GetVolume() == Approx(11.76).margin(0.01));
            CHECK(cone.GetMass() == Approx(298.48).margin(0.01));
            CHECK(cone.ToString() == "Cone\nDensity: 25.39\nVolume: 11.76\nMass: 298.48\nHeight: 2.57\nBaseRadius: 2.09\n");
        }
        AND_THEN("get cylinder") 
        {
            CHECK(cylinder.GetName() == "Cylinder");
            CHECK(cylinder.GetDensity() == 18.47);
            CHECK(cylinder.GetBaseRadius() == 0.69);
            CHECK(cylinder.GetHeight() == 10.87);
            CHECK(cylinder.GetVolume() == Approx(16.26).margin(0.01));
            CHECK(cylinder.GetMass() == Approx(300.29).margin(0.01));
            CHECK(cylinder.ToString() == "Cylinder\nDensity: 18.47\nVolume: 16.26\nMass: 300.29\nHeight: 10.87\nBaseRadius: 0.69\n");
        }
        AND_THEN("get parallelepiped") 
        {
            CHECK(parallelepiped.GetName() == "Parallelepiped");
            CHECK(parallelepiped.GetDensity() == 77.85);
            CHECK(parallelepiped.GetWidth() == 26.87);
            CHECK(parallelepiped.GetHeight() == 1.59);
            CHECK(parallelepiped.GetDepth() == 2.47);
            CHECK(parallelepiped.GetVolume() == Approx(105.53).margin(0.01));
            CHECK(parallelepiped.GetMass() == Approx(8215.24).margin(0.01));
            CHECK(parallelepiped.ToString() == "Parallelepiped\nDensity: 77.85\nVolume: 105.53\nMass: 8215.24\nWidth: 26.87\nHeight: 1.59\nDepth: 2.47\n");
        }
        AND_THEN("get compound") 
        {
            std::string compoundParams = "Compound\nDensity: 0.00\nVolume: 0.00\nMass: 0.00\n";
            std::string expectedResult = compoundParams.append("BEGIN_BODIES_IN_COMPOUND:\nEND_BODIES_IN_COMPOUND\n");
            CHECK(compound.GetName() == "Compound");
            CHECK(compound.GetDensity() == 0.0);
            CHECK(compound.GetVolume() == 0.0);
            CHECK(compound.GetMass() == 0.0);
            CHECK(compound.ToString() == expectedResult);
        }
        WHEN("add bodies to compound") 
        {
            auto compoundPtr = std::make_shared<CCompound>(compound);
            auto spherePtr = std::make_shared<CSphere>(sphere);
            auto cylinderPtr = std::make_shared<CCylinder>(cylinder);
            compoundPtr->AddChildBody(spherePtr);
            compoundPtr->AddChildBody(cylinderPtr);

            THEN("get compound parameters with child bodies") 
            {
                std::string totalInfo = "Compound\nDensity: 44.37\nVolume: 515.12\nMass: 22854.02\nBEGIN_BODIES_IN_COMPOUND:\nSphere\nDensity: 45.21\nVolume: 498.87\nMass: 22553.73\nRadius: 4.92\n\nCylinder\nDensity: 18.47\nVolume: 16.26\nMass: 300.29\nHeight: 10.87\nBaseRadius: 0.69\n\nEND_BODIES_IN_COMPOUND\n";
                CHECK(compoundPtr->GetDensity() == Approx(44.37).margin(0.01));
                CHECK(compoundPtr->GetVolume() == Approx(515.12).margin(0.01));
                CHECK(compoundPtr->GetMass() == Approx(22854.02).margin(0.01)); // Approx(22854.02).margin(0.01)); округление видимо зависит от машины
                CHECK(compoundPtr->ToString() == totalInfo);
            }
            AND_WHEN("add compound to compound") 
            {
                auto parallelepipedPtr = std::make_shared<CParallelepiped>(parallelepiped);
                auto conePtr = std::make_shared<CCone>(cone);
                CCompound compound2;
                auto compound2Ptr = std::make_shared<CCompound>(compound2);
                compound2Ptr->AddChildBody(parallelepipedPtr);
                compound2Ptr->AddChildBody(conePtr);
                compoundPtr->AddChildBody(compound2Ptr);
                THEN("get compound2 parameters")
                {
                    CHECK(compound2Ptr->GetDensity() == Approx(72.59).margin(0.01));
                    CHECK(compound2Ptr->GetVolume() == Approx(117.28).margin(0.01));
                    CHECK(compound2Ptr->GetMass() == Approx(8513.72).margin(0.01));
                    std::string p1 = "Compound\nDensity: 72.59\nVolume: 117.28\nMass: 8513.72\n";
                    std::string p2 = "BEGIN_BODIES_IN_COMPOUND:\nParallelepiped\nDensity: 77.85\nVolume: 105.53\nMass: 8215.24\nWidth: 26.87\nHeight: 1.59\nDepth: 2.47\n\n";
                    std::string p3 = "Cone\nDensity: 25.39\nVolume: 11.76\nMass: 298.48\nHeight: 2.57\nBaseRadius: 2.09\n\nEND_BODIES_IN_COMPOUND\n";
                    std::string expectedStr = p1 + p2 + p3;
                    CHECK(compound2Ptr->ToString() == expectedStr);
                }
                AND_THEN("get compound parameters with included compound") 
                {
                    std::string p1 = "Compound\nDensity: 49.60\nVolume: 632.41\nMass: 31367.75\n";
                    std::string p2 = "BEGIN_BODIES_IN_COMPOUND:\nSphere\nDensity: 45.21\nVolume: 498.87\nMass: 22553.73\nRadius: 4.92\n\n";
                    std::string p3 = "Cylinder\nDensity: 18.47\nVolume: 16.26\nMass: 300.29\nHeight: 10.87\nBaseRadius: 0.69\n\n";
                    std::string p4 = "Compound\nDensity: 72.59\nVolume: 117.28\nMass: 8513.72\n";
                    std::string p5 = "BEGIN_BODIES_IN_COMPOUND:\nParallelepiped\nDensity: 77.85\nVolume: 105.53\nMass: 8215.24\nWidth: 26.87\nHeight: 1.59\nDepth: 2.47\n\n";
                    std::string p6 = "Cone\nDensity: 25.39\nVolume: 11.76\nMass: 298.48\nHeight: 2.57\nBaseRadius: 2.09\n\nEND_BODIES_IN_COMPOUND\n\nEND_BODIES_IN_COMPOUND\n";
                    std::string expectedStr = p1 + p2 + p3 + p4 + p5 + p6;
                    CHECK(compoundPtr->ToString() == expectedStr);
                }
                AND_THEN("try input in compound his parent or himself") 
                {
                    CCompound compound3;
                    auto compound3Ptr = std::make_shared<CCompound>(compound3);
                    compound2Ptr->AddChildBody(compound3Ptr);
                    CHECK(compoundPtr->AddChildBody(compoundPtr) == false);
                    CHECK(compound2Ptr->AddChildBody(compoundPtr) == false);
                    CHECK(compound3Ptr->AddChildBody(compoundPtr) == false);
                }
                AND_THEN("try add to compound, compound that is already in another compound") 
                {
                    CCompound compound4;
                    auto compound4Ptr = std::make_shared<CCompound>(compound4);
                    REQUIRE(compound4Ptr->AddChildBody(compound2Ptr) == false);
                }
            }
        }
    }
}

TEST_CASE("Uncorrect create cone")
{
    std::string input = "cone 5 10 20 40\ncone 0 10 20\ncone 5 0 20\ncone 5 10 0\ncone -5 10 20\ncone 5 10\ncone a 10 20\n";
    std::istringstream in(input);
    std::ostringstream out;
    VolumetricSpace volumetricSpace(in, out);
    CHECK(volumetricSpace.HandleCommand() == false);
    CHECK(volumetricSpace.HandleCommand() == false);
    CHECK(volumetricSpace.HandleCommand() == false);
    CHECK(volumetricSpace.HandleCommand() == false);
    CHECK(volumetricSpace.HandleCommand() == false);
    CHECK(volumetricSpace.HandleCommand() == false);
    CHECK(volumetricSpace.HandleCommand() == false);
}

TEST_CASE("Uncorrect create cylinder")
{
    std::string input = "cylinder 5 10 20 40\ncylinder 0 10 20\ncylinder 5 0 20\ncylinder 5 10 0\ncylinder -5 10 20\ncylinder 5 10\ncylinder 5 10 15b\n";
    std::istringstream in(input);
    std::ostringstream out;
    VolumetricSpace volumetricSpace(in, out);
    CHECK(volumetricSpace.HandleCommand() == false);
    CHECK(volumetricSpace.HandleCommand() == false);
    CHECK(volumetricSpace.HandleCommand() == false);
    CHECK(volumetricSpace.HandleCommand() == false);
    CHECK(volumetricSpace.HandleCommand() == false);
    CHECK(volumetricSpace.HandleCommand() == false);
    CHECK(volumetricSpace.HandleCommand() == false);
}

TEST_CASE("Uncorrect create sphere")
{
    std::string input = "sphere 5 10 20\nsphere 0 10\nsphere 5 0\nsphere -5 10\nsphere 5 10 20\nsphere 5a 20\nsphere 5 20b\n";
    std::istringstream in(input);
    std::ostringstream out;
    VolumetricSpace volumetricSpace(in, out);
    CHECK(volumetricSpace.HandleCommand() == false);
    CHECK(volumetricSpace.HandleCommand() == false);
    CHECK(volumetricSpace.HandleCommand() == false);
    CHECK(volumetricSpace.HandleCommand() == false);
    CHECK(volumetricSpace.HandleCommand() == false);
    CHECK(volumetricSpace.HandleCommand() == false);
    CHECK(volumetricSpace.HandleCommand() == false);
}

TEST_CASE("Uncorrect create parallelepiped")
{
    std::string input = "parallelepiped 5 10 20 40 50\nparallelepiped 0 10 20 30\nparallelepiped 5 0 20 30\nparallelepiped 5 10 0 30\nparallelepiped -5 10 20 30\nparallelepiped 5 10 20 40 50 60\nparallelepiped 5 10 c 30\n";
    std::istringstream in(input);
    std::ostringstream out;
    VolumetricSpace volumetricSpace(in, out);
    CHECK(volumetricSpace.HandleCommand() == false);
    CHECK(volumetricSpace.HandleCommand() == false);
    CHECK(volumetricSpace.HandleCommand() == false);
    CHECK(volumetricSpace.HandleCommand() == false);
    CHECK(volumetricSpace.HandleCommand() == false);
    CHECK(volumetricSpace.HandleCommand() == false);
    CHECK(volumetricSpace.HandleCommand() == false);
}

TEST_CASE("Check Max Weight In Water Body and Body that has Max Mass")
{
    CParallelepiped parallelepiped1(997, 10, 10, 10);
    CParallelepiped parallelepiped2(1.2754, 100, 100, 100);
    std::string input = "parallelepiped 997 10 10 10\nparallelepiped 1.2754 100 100 100\n";
    std::string info = "Parallelepiped\nDensity: 997.00\nVolume: 1000.00\nMass: 997000.00\nWidth: 10.00\nHeight: 10.00\nDepth: 10.00\n\nParallelepiped\nDensity: 1.28\nVolume: 1000000.00\nMass: 1275400.00\nWidth: 100.00\nHeight: 100.00\nDepth: 100.00\n\n";

    std::istringstream in(input);
    std::ostringstream out;
    VolumetricSpace volumetricSpace(in, out);
    std::string maxWeight = volumetricSpace.leastWeightWater + "\nParallelepiped\nDensity: 1.28\nVolume: 1000000.00\nMass: 1275400.00\nWidth: 100.00\nHeight: 100.00\nDepth: 100.00\n";
    std::string maxMass = volumetricSpace.biggestMass + "\nParallelepiped\nDensity: 1.28\nVolume: 1000000.00\nMass: 1275400.00\nWidth: 100.00\nHeight: 100.00\nDepth: 100.00\n";
    std::string expectedOutput = info + maxMass + maxWeight;

    volumetricSpace.HandleCommand();
    volumetricSpace.HandleCommand();
    volumetricSpace.PrintBodiesInfo();
    volumetricSpace.PrintMaxMassBody();
    volumetricSpace.PrintBodyWithLeastWeightInWater();
    CHECK(out.str() == expectedOutput);
}
