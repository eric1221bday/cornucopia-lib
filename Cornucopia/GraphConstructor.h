/*--
    GraphConstructor.h  

    This file is part of the Cornucopia curve sketching library.
    Copyright (C) 2010 Ilya Baran (baran37@gmail.com)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GRAPHCONSTRUCTOR_H_INCLUDED
#define GRAPHCONSTRUCTOR_H_INCLUDED

#include "defs.h"
#include "Algorithm.h"

NAMESPACE_Cornu

struct Vertex
{
    int primitiveIdx;
    bool source;
    bool target;
    double cost;

    std::vector<int> edges; //edges that start at this vertex
};

struct Edge
{
    int startVtx;
    int endVtx;
    int continuity; //continuity = -1 for a dummy edge from a vertex to itself
    double cost; //includes the half the cost of the vertex behind and the vertex in front (full cost for source and target vertices).

    double validatedCost(const Fitter &fitter) const;
};

CORNU_SMART_FORW_DECL(Dataset);
CORNU_SMART_FORW_DECL(CostEvaluator);

template<>
struct AlgorithmOutput<GRAPH_CONSTRUCTION> : public AlgorithmOutputBase
{
    std::vector<Vertex> vertices;
    std::vector<Edge> edges;
    CostEvaluatorPtr costEvaluator;
    DatasetPtr dataset; //only if the algorithm selected is dataset generation
};

template<>
class Algorithm<GRAPH_CONSTRUCTION> : public AlgorithmBaseTemplate<GRAPH_CONSTRUCTION>
{
public:
    //override
    std::string stageName() const { return "Graph Constructor"; }

private:
    friend class AlgorithmBase;
    static void _initialize();
};

END_NAMESPACE_Cornu

#endif //GRAPHCONSTRUCTOR_H_INCLUDED
