
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
    void draw( bool all = true );
    void new_cut( vec2 p, cut_type t );
    
    void erase();
    void previous();
    void next();
    
    void save( FILE *fp ); 
    void save_program( FILE *fp ); 
    
    void load( FILE *fp );
    
    void create_contour( contour_path &p );
    void create_contour(){ create_contour( contour ); };
    
    void create_path( operation &ccontour, operation &ctool );

    op_type get_type(){ return type; };
    
    private:
    op_type type; 
    
    // shape
    list<struct cut>::iterator currentcut;
    std::list<struct cut> cl;
    Side side;
    contour_path contour;
    bool changed;
    
    // tool
    tool tl;
    
    // rough 
    rough_path r_path;
    
    vec2 min,max; 
};






