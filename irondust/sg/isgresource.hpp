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


#ifndef ISGRESOURCE_HPP
#define ISGRESOURCE_HPP

namespace irondust
{
    namespace sg
    {
        class SGContext;

        class ISGResource
        {
        public:
            virtual ~ISGResource() = default;

            virtual bool init(SGContext& context) = 0;
        };
    }
}

#endif // ISGRESOURCE_HPP
