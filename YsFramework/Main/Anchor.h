#ifndef ANCHOR_H
#define ANCHOR_H

#include <stdio.h>
#include <vector>
#include <math.h>
#include <ysshellext.h>
#include <ysclass.h>

#include "mihashtable.h"
#include "clustering.h"
#include "vertex_to_polygon.h"

//using namespace std;

template<>
inline long long int HashTable<YSHASHKEY,int>::HashCode(const YSHASHKEY &key) const
{
    return key;
}


class AncVtx
{
public:
    YsVec3 Anchor;
    std::vector<int> label;
    YsShell::VertexHandle Ptr;
    
public:
    inline AncVtx &operator=(AncVtx &incoming)
    {
        if(this!=&incoming)
        {
            this->Anchor = incoming.Anchor;
            this->label = incoming.label;
            this->Ptr = incoming.Ptr;
        }
        
        return *this;
    }
        

};

struct PxyVtx
{
public:
    YsShell::VertexHandle Anchor;
    int label1,label2;
};

typedef std::vector<AncVtx> AncVtxHandle; 

class AnchorVertex
{
protected:
    int k;
    const YsShellExt *shl;
    const LloydCluster *MyCl;
    AncVtxHandle AncPts;
    std::vector<AncVtxHandle> PrxyAnc;
    std::vector<std::vector<PxyVtx>> Vtxlst;
    class VertexTable : public HashTable<YSHASHKEY,int>
    {
    public:
        inline int GetLabelForVertex(YsShell::VertexHandle vtHd, const YsShellExt &shl)
        {
            return *(*this)[shl.GetSearchKey(vtHd)];
        }
    };
public:
    VertexTable VertexToLabel;
    inline AnchorVertex()
    {
        
    }
    inline AnchorVertex(int k)
    {
        this->k=k;
    }
   ~AnchorVertex();
    void Initialize(const YsShellExt &s, const LloydCluster &MC);
    void MakeAnchorVertex();
    void BinAnchorVertex();
    void FindAverageAnchorVertex(AncVtx &vtx);
    void AssignLabel();
    AncVtxHandle GetAnchorVtx(int ProxyNum);
    AncVtxHandle GetNeighbourAnc(AncVtx VtxHd, AncVtxHandle PxHd);
    std::vector<PxyVtx> GetEdgeVertices(AncVtx vtx1, AncVtx vtx2, int ClusterNum);
    void AddAncVtx(AncVtx vtx1, AncVtx vtx2, std::vector<PxyVtx> EdgeVtx, int ClusterNum);
    void ExtractEdges(int ClusterNum);
    YsShellExt IndexLabelling();

};





#endif