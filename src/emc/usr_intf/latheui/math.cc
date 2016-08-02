#include "latheintf.h"

// inSegment(): determine if a point is inside a segment
//    Input:  a point P, and a collinear segment S
//    Return: 1 = P is inside S
//            0 = P is  not inside S
int
inSegment( vec2 P, vec2 S1, vec2 S2)
{
    if (S1.x != S2.x) {    // S is not  vertical
        if (S1.x <= P.x && P.x <= S2.x)
            return 1;
        if (S1.x >= P.x && P.x >= S2.x)
            return 1;
    }
    else {    // S is vertical, so test y  coordinate
        if (S1.z <= P.z && P.z <= S2.z)
            return 1;
        if (S1.z >= P.z && P.z >= S2.z)
            return 1;
    }
    return 0;
}

#define SMALL_NUM 0.000001
//===================================================================
// dot product (3D) which allows vector operations in arguments
#define DOT(u,v)   (u.dot(v))  //)((u).x * (v).x + (u).z * (v).z)
#define PERP(u,v)  (u.perp(v))

int get_line_intersection( vec2 S1P0, vec2 S1P1 , vec2 S2P0, vec2 S2P1, vec2 &I0 )
{
    vec2    u = S1P1 - S1P0;
    vec2   v = S2P1 - S2P0;
    vec2    w = S1P0 - S2P0;
    double     D = PERP(u,v);

    // test if  they are parallel (includes either being a point)
    if (fabs(D) < SMALL_NUM) {           // S1 and S2 are parallel
        if (PERP(u,w) != 0 || PERP(v,w) != 0)  {
            return 0;                    // they are NOT collinear
        }
        // they are collinear or degenerate
        // check if they are degenerate  points
        double du = DOT(u,u);
        double dv = DOT(v,v);
        if (du==0 && dv==0) {            // both segments are points
            if (S1P0 !=  S2P0)         // they are distinct  points
                 return 0;
            I0 = S1P0;                 // they are the same point
            return 1;
        }
        if (du==0) {                     // S1 is a single point
            if  (inSegment(S1P0, S2P0, S2P1 ) == 0)  // but is not in S2
                 return 0;
            I0 = S1P0;
            return 1;
        }
        if (dv==0) {                     // S2 a single point
            if  (inSegment(S2P0, S1P0, S1P1 ) == 0)  // but is not in S1
                 return 0;
            I0 = S2P0;
            return 1;
        }
        // they are collinear segments - get  overlap (or not)
        double t0, t1;                    // endpoints of S1 in eqn for S2
        vec2 w2 = S1P1 - S2P0;
        if (v.x != 0) {
                 t0 = w.x / v.x;
                 t1 = w2.x / v.x;
        }
        else {
                 t0 = w.z / v.z;
                 t1 = w2.z / v.z;
        }
        if (t0 > t1) {                   // must have t0 smaller than t1
                 double t=t0; t0=t1; t1=t;    // swap if not
        }
        if (t0 > 1 || t1 < 0) {
            return 0;      // NO overlap
        }
        t0 = t0<0? 0 : t0;               // clip to min 0
        t1 = t1>1? 1 : t1;               // clip to max 1
        if (t0 == t1) {                  // intersect is a point
            I0 = S2P0 +  v*t0;
            return 1;
        }

        // they overlap in a valid subsegment
        if( S1P0.dist_squared( S2P0 + v*t0 ) <  S1P0.dist_squared( S2P0 + v*t1 ))
        {
            I0 = S2P0 + v*t0;
        }
        else
        {
            I0 = S2P0 + v*t1;
        }
        return 2;
    }

    // the segments are skew and may intersect in a point
    // get the intersect parameter for S1
    double     sI = PERP(v,w) / D;
    if (sI < 0 || sI > 1)                // no intersect with S1
        return 0;

    // get the intersect parameter for S2
    double     tI = PERP(u,w) / D;
    if (tI < 0 || tI > 1)                // no intersect with S2
        return 0;

    I0 = S1P0 + u*sI;                // compute S1 intersect point
    return 1;
}
//===================================================================


void findtag( const char *line, const char *tag, double &val,const double v )
{
    if( strcmp( tag, line ) == 0 )
    {
        val = v;
    }      
}

void findtag( const char *line, const char *tag, int &val,const int v )
{
    if( strcmp( tag, line ) == 0 )
    {
        val = v;
    }      
}

void findtag( const char *line, const char *tag, bool &val,const int v )
{
    if( strcmp( tag, line ) == 0 )
    {
        val = (bool)v;
    }      
}


void findtag( const char *line, const char *tag, char *str )
{
    
    if( strstr( line, line ) == line )
    {
        sscanf( line, "%*[^\"]\"%255[^\"]\"", str);
    }      
}

void loadtagl( FILE *fp, list<ftag> &tagl )
{
    if (fp == NULL) return;
    
    char *line = NULL;
    size_t len = 0;   
    ssize_t read;
    char tag[BUFFSIZE+1];
    
    double val;

    while ((read = getline( &line, &len, fp)) != -1)
    {

        printf("load %s", line);
        
        val = 0;
        sscanf(line, "%s %lf", tag, &val );
        
        for( list<ftag>::iterator i = tagl.begin(); i != tagl.end(); i++)
        {
            if( strcmp( tag, i->tag ) == 0 )
            {
                switch( i->type )
                {
                    case T_INT:
                        *(int*)i->val = (int)val;
                    break;
                    
                    case T_DOUBLE:
                        *(double*)i->val = val;
                    break;
                  
                    case T_BOOL:
                        *(bool*)i->val = (bool)val;
                    break;  
                             
                    case T_CHAR:
                        sscanf( line, "%*[^\"]\"%255[^\"]\"", (char*)i->val);
                    break;               
                } 
            }
        }
        
        free(line);
        line = NULL;
        
        if( strcmp( tag, "END" ) == 0 )
        {
            break;
        }      
    }
       
}

void savetagl( FILE *fp, list<ftag> &tagl )
{
    if (fp == NULL) return;
    
    for( list<ftag>::iterator i = tagl.begin(); i != tagl.end(); i++)
    {
        switch( i->type )
        {
            case T_INT:
                fprintf(fp, "   %s %i\n", i->tag, *(int*)i->val );
            break;
            
            case T_DOUBLE:
                fprintf(fp, "   %s %.8g\n", i->tag, *(double*)i->val );
            break;
          
            case T_BOOL:
                fprintf(fp, "   %s %i\n", i->tag, (int)*(bool*)i->val );
            break;  
                     
            case T_CHAR:
                fprintf(fp, "   %s %s\n", i->tag, (char*)i->val );
            break;               
        }
    }
    
    fprintf(fp, "END\n" );
}





