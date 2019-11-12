// (C) 2019 by CyberViking Softwareschmiede GbR
// All rights reserved.
// -----------------------------------------------------
// created by: armin
// created on: 12.05.2019
// -----------------------------------------------------
// This document contains proprietary information belonging to
// CyberViking Softwareschmiede GbR.
// Passing on and copying of this document, use and communication
// of its contents is not permitted without prior written authorization.


#include "sgcontext.hpp"


namespace irondust
{
    namespace sg
    {
        SGContext::SGContext(SGScene& scene)
            : program(nullptr)
            , scene(scene)
            , scene_matrix(1.f)
        {
        }

        SGContext::~SGContext()
        {
        }
    }
}