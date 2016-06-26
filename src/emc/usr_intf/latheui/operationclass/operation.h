
const char* phase_name( int t );

class operation
{
    public:

    operation( op_type t );
    ~operation();
    
    const char* get_name();
    
    // shape
    cut get_cut();
    void set_cut( cut &c );
    
    // tool
    tool get_tool();
    void set_tool( tool &c );
    
    //void set_inside( bool s ){ inside = s;} 
    Side get_side(){ return side; }; 
    void draw( int x1,int y1,int x2,int y2);
    void new_cut( vec2 p, cut_type t );
    
    void erase();
    void previous();
    void next();
    void save( FILE *fp ); 
    void load( FILE *fp );
    void create_contour( contour_path &p );
    void create_path( operation &ccontour, operation &ctool, Side s );

    op_type get_type(){ return type; };
    
    private:
    op_type type; 
    
    // shape
    list<struct cut>::iterator currentcut;
    std::list<struct cut> cl;
    Side side;
    contour_path contour;
    
    // tool
    tool tl;
    
    // rough 
    rough_path r_path;
    
    double scale;
    vec2 pos;
    vec2 min,max; 
};






