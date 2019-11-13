/**
 ** This file is part of the irondust project.
 ** Copyright 2019 CyberViking Softwareschmiede GbR <leghissa@cyber-viking.com>.
 **
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU Lesser General Public License as
 ** published by the Free Software Foundation, either version 3 of the
 ** License, or (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU Lesser General Public License for more details.
 **
 ** You should have received a copy of the GNU Lesser General Public License
 ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **/


#ifndef SGNODE_HPP
#define SGNODE_HPP

#include <irondust/sg/isgnode.hpp>

#include <vector>
#include <initializer_list>

namespace irondust
{
    namespace sg
    {
        class SGNode : public ISGNode
        {
        public:
            SGNode();
            SGNode(const std::vector<ISGNode*>& children);
            SGNode(const std::initializer_list<ISGNode*>& children);
            SGNode(ISGNode* child);

            virtual ~SGNode() override;

            virtual ISGNode& append(ISGNode* node) override;
            virtual bool remove(ISGNode* node) override;
            virtual void render(SGContext& context) override;

        private:
            void* children;
            bool single;
        };
    }
}

#endif // SGNODE_HPP
