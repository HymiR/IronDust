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


#ifndef SGSCENE_HPP
#define SGSCENE_HPP

#include <irondust/sg/sgcontext.hpp>

#include <vector>


namespace irondust
{
    namespace sg
    {
        class ISGNode;
        class ISGResourceNode;

        class SGScene
        {
        public:
            SGScene(ISGNode* root=nullptr);
            virtual ~SGScene();

            ISGNode& getRoot();
            SGContext& getContext();

            void record(ISGResourceNode* res);
            bool init();
            void render();

        private:
            SGContext context;
            ISGNode* root;
            std::vector<ISGResourceNode*> resources;
        };
    }
}

#endif // SGSCENE_HPP
