// (C) 2019 by CyberViking Softwareschmiede GbR
// All rights reserved.
// -----------------------------------------------------
// created by: armin
// created on: 14.05.2019
// -----------------------------------------------------
// This document contains proprietary information belonging to
// CyberViking Softwareschmiede GbR.
// Passing on and copying of this document, use and communication
// of its contents is not permitted without prior written authorization.


#ifndef ISGELEMENT_HPP
#define ISGELEMENT_HPP

namespace cg
{
    class SGContext;

    class ISGElement
    {
    public:
        virtual ~ISGElement() = default;

        virtual void render(SGContext& context) = 0;
    };
}

#endif // ISGELEMENT_HPP