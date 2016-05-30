#include "../latheintf.h"

extern const double retract;
extern const double stockdiameter;
extern char strbuf[BUFFSIZE];
extern const int maxrpm;
extern const vec2 startposition;

void undercut_path::create( contour_path &c )
{
    
    tc.create( c, cp.tool_r );
    
    double x = 0;
    ml.clear();
    if( ! tc.ml.empty() )
    {
        for(list<struct mov>::iterator i = tc.ml.begin(); i != tc.ml.end(); i++)
        {
    
            if( i->end.x > i->start.x ) // uphill
            {
                while( x < i->end.x ) x += cp.depth;
            }
            else  // downhill
            {
                while( x > i->start.x ) x -= cp.depth;
                if( i->end.x < x )
                {
                    double dx = i->end.x - i->start.x;
                    double dz = i->end.z - i->start.z;
        
                    while( x > i->end.x )
                    {
                        double z = i->start.z + dz * (x - i->start.x) / dx;
                        if( z > tc.min.z )
                        {
                             feed_to_left( tc, next(i,1), vec2( x, z ), fabs( c.min.z -z ) );
                        }
                        x -= cp.depth;
                    }
                    
                }
            }
        }
    }
    findminmax();
}

void undercut_path::draw( bool b )
{
    path::draw(b);
    tc.draw(b);
}
