#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;
///////////////////////////////////////////////////////// macros
#define MXSPD  2 // yea! ------------------------- maximum speed
// Becz we r restricted to 50 nodes we can use vtx ASCII - index
// mapping. Data in adj (see globals) should be placed _________
// consequentially representing AB...Zab..x vertices ___________
#define GAP ('a' - '[') //............ nof chars betveen Z and a
#define ABC ('[' - 'A') //.............. nof alphabet characters
#define shl(V) (V - 'A')
#define shr(J)                                         (J + 'A')
#define v2j(V) /*      ze        */ shl(V) - ((V < 'a')? 0: GAP)
#define j2v(J) /*      mapping   */ shr(J) + ((J < ABC)? 0: GAP)
#define srch(C,V)         (find(C.begin(),C.end(),V) != C.end())
////////////////////////////////////////////////////////// types
typedef vector<string>        vstr_t; //
typedef vector<int>           vint_t; // yeah! (BuHToBKa)
typedef vector<struct snod *> stck_t; // stack
typedef vector<string *>      vstp_t; // boom
namespace gb { ///////////////////////////////////////// globals
////////////////////////////////////////////////////////// data:
    const vstr_t adj[] = {
	{
        "BD",  // A   E     -                                  0
        "AC",  // B  / \    - backslash hack
        "BDE", // C D---C   -
        "ACE", // D  \   \  -
        "CD"   // E   A---B -
	},{
        "BE",  // A                                            1
        "ACD", // B   G---F   *
        "BF",  // C  /   / \  *
        "BEF", // D E---D   C *
        "ADG", // E  \   \ /  *
        "CDG", // F   A---B   *
        "EF"   // G
	},{
        "BC",   // A                                           2
        "ACD",  // B
        "ABDE", // C A---C---E---G "
        "BCEF", // D  \ / \ / \ /  "
        "CDFG", // E   B---D---F   "
        "DEG",  // F
        "EF"    // G
    },{
        "B",    // A                                           3
        "ACEF", // B A---B---C---D     *
        "BD",   // C    / \     / \    *
        "CGH",  // D   E   F---G   H   *
        "BI",   // E  /   / \ /     \  *
        "BGJK", // F I---J   K---L---M *
        "DFK",  // G
        "DM",   // H
        "EJ",   // I
        "FI",   // J
        "FGL",  // K
        "KM",   // L
        "HL"    // M
    },{
        "B",     // A A---B   K         *                      4
        "AC",    // B      \ /          *
        "BKLMD", // C       C---L       *
        "CEU",   // D      / \ /        *
        "DNF",   // E U---D   M         *
        "EG",    // F    /   / \        *
        "FH",    // G   E---N   T---S   *
        "GOI",   // H  /     \     /    *
        "HPJWV", // I F---G   Q---R     *
        "I",     // J      \            *
        "C",     // K       H---O---X   *
        "CM",    // L      /   /   /    *
        "CLTN",  // M V---I---P   Y---Z *
        "MQE",   // N  \ / \            *
        "HX",    // O   W   J           *
        "IO",    // P
        "NR",    // Q
        "QS",    // R
        "TR",    // S
        "MS",    // T
        "D",     // U
        "IW",    // V
        "VI",    // W
        "OY",    // X
        "XZ",    // Y
        "Y"      // Z        
    },{
        "BD",     // A                                         5
        "ACF",    // B
        "BG",     // C
        "AEIH",   // D     A---B---C         ,
        "DFI",    // E    /     \   \        ,
        "BGKE",   // F   D---E---F---G       ,
        "CLF",    // G  / \ /     \   \      ,
        "DN",     // H H   I---J---K---L---M ,
        "DEJON",  // I  \ / \     / \     /  ,
        "IK",     // J   N   O---P---Q---R   ,
        "FLQPJ",  // K  / \ /     \ /   /    ,
        "GKM",    // L S---T---U---V   W     ,
        "LR",     // M  \ / \ / \       \    ,
        "HITS",   // N   X   Y---Z---a---b   ,
        "IPT",    // O    \ /   / \          ,
        "KQVO",   // P     c---d---e         ,
        "KRVP",   // Q    /     \ /          ,
        "MWQ",    // R   f---g---h           ,
        "NTX",    // S    \     /            ,
        "NOUYXS", // T     i---j       k     ,
        "VZYT",   // U    / \ / \     / \    ,
        "PQU",    // V   l---m---n---o---p   ,
        "Rb",     // W    \ /     \ / \ /    ,
        "STc",    // X     q---r---s---t     ,
        "TUZc",   // Y          \ / \ / \    ,
        "UaedY",  // Z           u---v---w   ,
        "Zb",     // a            \ /        ,
        "aW",     // b             x         ,
        "XYdf",   // c
        "Zehc",   // d
        "Zhd",    // e
        "cgi",    // f
        "fh",     // g
        "dejg",   // h
        "fjml",   // i
        "hnmi",   // j
        "po",     // k
        "imq",    // l
        "ijnql",  // m
        "josm",   // n
        "kptsn",  // o
        "kto",    // p
        "lmr",    // q
        "qsu",    // r
        "notvur", // s
        "opwvs",  // t
        "rsvx",   // u
        "stwxu",  // v
        "tv",     // w
        "uv"      // x
    }};
    const string network[] = {
        "   E               \n"
        "  / \\             \n"
        " D---C             \n"
        "  \\   \\          \n"
        "   A---B           \n",
        "   G---F           \n"
        "  /   / \\         \n"
        " E---D   C         \n"
        "  \\   \\ /        \n"
        "   A---B           \n",
        " A---C---E---G     \n"
        "  \\ / \\ / \\ /   \n"
        "   B---D---F       \n",
        " A---B---C---D     \n"
        "    / \\     / \\  \n"
        "   E   F---G   H   \n"
        "  /   / \\ /     \\\n"
        " I---J   K---L---M \n",
        " A---B   K         \n"
        "      \\ /         \n"
        "       C---L       \n"
        "      / \\ /       \n"
        " U---D   M         \n"
        "    /   / \\       \n"
        "   E---N   T---S   \n"
        "  /     \\     /   \n"
        " F---G   Q---R     \n"
        "      \\           \n"
        "       H---O---X   \n"
        "      /   /   /    \n"
        " V---I---P   Y---Z \n"
        "  \\ / \\          \n"
        "   W   J           \n",
        "     A---B---C             \n"
        "    /     \\   \\          \n"
        "   D---E---F---G           \n"
        "  / \\ /     \\   \\       \n"
        " H   I---J---K---L---M     \n"
        "  \\ / \\     / \\     /   \n"
        "   N   O---P---Q---R       \n"
        "  / \\ /     \\ /   /      \n"
        " S---T---U---V   W         \n"
        "  \\ / \\ / \\       \\    \n"
        "   X   Y---Z---a---b       \n"
        "    \\ /   / \\            \n"
        "     c---d---e             \n"
        "    /     \\ /             \n"
        "   f---g---h               \n"
        "    \\     /               \n"
        "     i---j       k         \n"
        "    / \\ / \\     / \\     \n"
        "   l---m---n---o---p       \n"
        "    \\ /     \\ / \\ /     \n"
        "     q---r---s---t         \n"
        "          \\ / \\ / \\     \n"
        "           u---v---w       \n"
        "            \\ /           \n"
        "             x             \n"
    };
    int         config; // network configuration ---------------
// NEIGHBORS: //////////////////////////////////////////////////
//           If we take the adj[0] case with robots initially at
// C and E having speeds 1 and 2 respectively, than vhen the 1st
//   robot arrives at one of the three vertices BDE, the 2nd one
//    can be at any of the following five vertices: ACEBD. So we
//  refer to this possibilities as nbor[1] and [2] respectively.
    vstr_t      nbor[MXSPD + 1];
    struct snod *root;
    vint_t      spd; // sp e    e                          d
///////////////////////////////////////////////////////// f ecs:
    void init(void); 
}
///////////////////////////////////////////////////////// funcs:
void nodup_ush(string *dst, const string &src) /////////////////
//           no duplication push_back characters from src to dst
{
    for (char c: src) {
        if (dst->find(c) == string::npos) dst->push_back(c);
    }
} //////////////////////////////////////////////////////////////
string getlvel(uint lvel, const char &root) /// get lvel's nodes
// > lvel  - level
// > root  - tree root (level 0)
// < oufut : lvel's nodes
{
    const vstr_t &hood = gb::nbor[1]; 
    
    string *cld = new string();        // child
    string *par = new string(1, root); // parent nodes
    
    while (lvel--) {
        for (char vtx: *par) nodup_ush(cld, hood[v2j(vtx)]);
        swap<string *>(par, cld);
        cld->clear();
    }
    return *par;
} //////////////////////////////////////////////////////////////
///////////////////////////////////////////////////// rpyna K7ac
struct snod { // tree search node
    const string robots; // robots' current vertex positions
    snod *par;           // parent back connection

    snod(const string &robots, snod *par);
    friend 
    ostream &operator<<(ostream &out, const snod &nod);
    bool    arvedon(void);    // that's the question?
    stck_t  *grin_desc(void); // gradient descent
}; /////////////////////////////////////////////////////////////
snod::snod(const string &robots, snod *par): ///////////////////
    robots{robots}, par{par}
{} /////////////////////////////////////////////////////////////
ostream &operator<<(ostream &out, const snod &nod) /////////////
{
    out << "snod(" << nod.robots << ", " << nod.par << ")";

    return out;
} //////////////////////////////////////////////////////////////
bool snod::arvedon(void) ///////////////////////////////////////
// ck whether all robots' vertices are same
{
    const string &robots = this->robots;
    const char   &vtx    = robots[0];

    uint j = robots.size();
    
    while (--j) if (robots[j] != vtx) return false;

    return true;
} //////////////////////////////////////////////////////////////
stck_t *snod::grin_desc(void) //            
//  < oufut : _
// A key function, returns a list of all possible child nodes.
{
    const string &robots = this->robots;
    const int8_t len = robots.size();

    bool cross(vint_t &vi, const vint_t &mx);
    
    int8_t i, j, s, v;
    vint_t vi(len, 0);
    vint_t mx(len, 0);
    vstp_t hood(len, nullptr);
    stck_t *stck = new stck_t();
    string buf(len, 0);

    for (j = 0; j < len; j++) {
        v = robots[j];  // vertex
     	i = v2j(v);     // v-mapping
     	s = gb::spd[j]; // yeah!
	
        hood[j] = &(gb::nbor[s][i]);
        mx[j]   = hood[j]->size() - 1;
    }
    do {
        for (j = 0; j < len; j++) {
            buf[j] = (*hood[j])[vi[j]];
        }
        stck->push_back(new snod(buf, this));	
    } while (cross(vi, mx));
    
    return stck;
} //////////////////////////////////////////////////////////////
void gb::init(void) ////////////////////////////////////////////
{
    config = 5;

    nbor[0] = {};          // dummy record
    nbor[1] = adj[config]; // Copy Ninja Kakashi ...............

    for (auto j = 0; j < nbor[1].size(); j++) {
        nbor[2].push_back(getlvel(2, j2v(j)));
    }
    spd = { 2, 1, 1 };
    root = new snod("JYh", nullptr);
    
    return;
} ///////////////////////////////////////////////// dump fector:
template <typename T>
ostream &operator<<(ostream &out, vector<T> vec) ///////////////
{
    const string sep = ", ";
    
    string str;
    stringstream buf;
  
    for (auto &elm: vec) buf << elm << sep;

    str = buf.str();
    
    // dump vithout last separator:
    out << str.substr(0, str.size() - sep.size()) << endl;

    return out;
}
bool cross(vint_t &vi, const vint_t &mx) ///// Cartesian product
// <> vi    - index vector
//  > mx    - vi inclusive upper bounds
//  < oufut : false if all variants are exhausted
{
    int k = vi.size() - 1;
    
    while (vi[k] == mx[k]) {
        vi[k--] = 0;
        if (k < 0) return false; // ve ar don!!
    }
    return ++vi[k];
} ///////////////\\/////////////////////////////////////////////
snod *lvelscan(snod *root) /////////////////////////////////////
// > root  - tree root
// < oufut : solution node or nullptr
{
    stck_t *parstck = new stck_t(1, root); //       parent stack
    stck_t *chlstck = new stck_t(); //               child stack
    stck_t auxstck{root}; //            auxilary (history) stack

    while (true) {
        for (snod *parnod: *parstck) {
    	    for (snod *chlnod: *(parnod->grin_desc())) {
                if (chlnod->arvedon()) return chlnod;
                if (!srch(auxstck, chlnod)) {
                    chlstck->push_back(chlnod);
                    auxstck.push_back(chlnod);
                }
    	    }
    	}
        if (chlstck->empty()) return nullptr;
        swap<stck_t *>(parstck, chlstck);
     	chlstck->clear();
    }
} //////////////////////////////////////////////////////////////
vstr_t *beacon(snod *nod) // nod shouldn't be nullptr
{
    vstr_t *ls = new vstr_t();

    do { ls->push_back(nod->robots); } while (nod = nod->par);

    reverse(ls->begin(), ls->end());

    return ls;
}
void tsto(void) ////////////////////////////////////////////////
{
    int pOOM;

    exit(pOOM);
} //////////////////////////////////////////////////////////////
int main(void) /////////////////////////////////////////////////
{
    using namespace gb;

    init();

    snod *nod = lvelscan(root);

    cout << network[config] 
         << "speed:   " << spd
         << "nbor[1]: " << nbor[1]
         << "nbor[2]: " << nbor[2]
         << "root:    " << *root << endl;

    if (nod == nullptr) {
        cout << "No solution.\n";
    } else {
        cout << *nod << endl << *beacon(nod);
    }
    return 0;
} ///////////////////////////////////////////////////////// log:
