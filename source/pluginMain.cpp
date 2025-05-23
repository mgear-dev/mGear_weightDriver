// ---------------------------------------------------------------------
//
//  pluginMain.cpp
//
//  Created by ingo on 10/5/13.
//  Copyright (c) 2021 Ingo Clemens. All rights reserved.
//
// ---------------------------------------------------------------------

#include <string>

static const std::string kVERSION = "3.6.3";

#include <maya/MFnPlugin.h>

#include "mGearWeightDriver.h"

// VP2.0
#if MAYA_API_VERSION >= 201400
#include <maya/MDrawRegistry.h>
#endif

// ---------------------------------------------------------------------
// initialization
// ---------------------------------------------------------------------

MStatus initializePlugin(MObject obj)
{
    MStatus status;
    MFnPlugin plugin(obj, "Ingo Clemens (mGear Version)", kVERSION.c_str(), "Any");

// VP2.0
#if MAYA_API_VERSION >= 201400
    status = plugin.registerNode("mGearWeightDriver",
                                 mGearWeightDriver::id,
                                 &mGearWeightDriver::creator,
                                 &mGearWeightDriver::initialize,
                                 MPxNode::kLocatorNode,
                                 &mGearWeightDriver::drawDbClassification);
    if (status != MStatus::kSuccess)
        status.perror("Register mGearWeightDriver command failed");

    status = MHWRender::MDrawRegistry::registerDrawOverrideCreator(mGearWeightDriver::drawDbClassification,
                                                                   mGearWeightDriver::drawRegistrantId,
                                                                   mGearWeightDriverOverride::Creator);
    if (status != MStatus::kSuccess)
        status.perror("Register DrawOverrideCreator for mGearWeightDriver command failed");
#else
    status = plugin.registerNode("mGearWeightDriver",
                                 mGearWeightDriver::id,
                                 mGearWeightDriver::creator,
                                 mGearWeightDriver::initialize,
                                 MPxNode::kLocatorNode);
    if (status != MStatus::kSuccess)
        status.perror("Register mGearWeightDriver command failed");
#endif

    return status;
}

MStatus uninitializePlugin(MObject obj)
{
    MStatus status;
    MFnPlugin plugin(obj, "Ingo Clemens (mGear Version)", kVERSION.c_str(), "Any");

// VP2.0
#if MAYA_API_VERSION >= 201400
    status = MHWRender::MDrawRegistry::deregisterDrawOverrideCreator(mGearWeightDriver::drawDbClassification,
                                                                     mGearWeightDriver::drawRegistrantId);
    if (status != MStatus::kSuccess)
        status.perror("Deregister DrawOverrideCreator for mGearWeightDriver command failed");
#endif

    status = plugin.deregisterNode(mGearWeightDriver::id);

    if (status != MStatus::kSuccess)
        status.perror("Deregister mGearWeightDriver command failed");

    return status;
}

// ---------------------------------------------------------------------
// MIT License
//
// Copyright (c) 2021 Ingo Clemens, brave rabbit
// mGearWeightDriver is under the terms of the MIT License
//
// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:
//
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
// CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
// Author: Ingo Clemens    www.braverabbit.com
// ---------------------------------------------------------------------
