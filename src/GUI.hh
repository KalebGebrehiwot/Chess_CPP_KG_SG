#ifndef GUI_HH__
#define GUI_HH__

#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_Output.H>
#include "Attributes.hh"
#include "Point.hh"
#include "Widget.hh"
#include "Window.hh"
#include <functional>
#include <map>
#include <sstream>

namespace AUGL {

  /**
   * @class Button
   * @author ngrau@augie.edu
   * @date Fall 2024
   * @brief A Button widget
   */
  class Button : public Widget {
  public:

    /**
     * @brief Construct a button from a point, width, heigh, label, and callback
     */
    Button(const Point& p, int width, int height, const Text& label, Callback_t callback) : Widget(p,width,height,label,callback) {}

    /**
     * @brief Overrides Widget::attach()
     *
     * Creates the button with the correct attributes
     */
    void attach(Window* w) {
      m_owner = w;
      m_widget = new Fl_Button(m_point.x,m_point.y,m_width,m_height,m_label.c_str());
      m_widget->callback(reinterpret_cast<Fl_Callback*>(m_callback),m_owner);
      m_widget->labelcolor(m_label.textcolor());
      m_widget->labelfont(m_label.textstyle());
      m_widget->labelsize(m_label.textsize());
    }
  };

  /**
   * @class LabelBox
   * @author ngrau@augie.edu
   * @date Fall 2024
   * @brief A simple box widget for labeling
   */
  class LabelBox : public Widget {
  public:

    /**
     * @enum BoxType_t
     * @brief Wrapper enum to give named constants to FLTKs box type integers
     */
    enum BoxType_t {
      NO_BOX=FL_NO_BOX,
      FLAT_BOX=FL_FLAT_BOX,
      UP_BOX=FL_UP_BOX,
      DOWN_BOX=FL_DOWN_BOX
    };

    /**
     * @brief construct a label with a point, width, height, label, and (optionally) box type
     */
    LabelBox(const Point& p, int width, int height, const Text& label, BoxType_t type=NO_BOX) : Widget(p,width,height,label,nullptr) {
      m_boxtype = static_cast<Fl_Boxtype>(static_cast<int>(type));
    }

    /**
     * @brief attach this widget to the window
     */
    void attach(Window* w) {
      m_owner = w;
      m_widget = new Fl_Box(m_point.x,m_point.y,m_width,m_height,m_label.c_str());
      m_widget->box(m_boxtype);
      m_widget->labelcolor(m_label.textcolor());
      m_widget->labelfont(m_label.textstyle());
      m_widget->labelsize(m_label.textsize());
    }

  private:
    Fl_Boxtype m_boxtype; //!the outline of the box in FLTK
  };

  /**
   * @class Input
   * @author ngrau@augie.edu
   * @date Fall 2024
   * @brief Single line of text for input
   */
  class Input : public Widget {
  public:

    /**
     * @brief construct the Input object with an upper left point, width, height, a default text
     */
    Input(const Point& p, int width, int height, const Text& defaultText) : Widget(p,width,height,defaultText,nullptr), m_border(nullptr) {
      setFillColor(Color::WHITE);
    }

    /**
     * @brief The destructor
     */
    virtual ~Input(){
      delete m_border;
    }

    /**
     * @brief Override void Widget::attach() to attach this input box to the window
     */
    void attach(Window* w){
      m_owner = w;
      Fl_Input *input = new Fl_Input(m_point.x,m_point.y,m_width,m_height,m_label.c_str());
      m_widget = input;
      m_widget->color(fillColor(),fillColor());
      //set the default value
      input->static_value(m_label.c_str());
      //not sure why I need to do this piece...
      //but build a 1pt white border around the input box
      m_border = new LabelBox({m_point.x-1,m_point.y-1},m_width+2,m_height+2,{""},LabelBox::DOWN_BOX);
      m_border->setFillColor(Color::WHITE);
      w->attach(*m_border);
    }

    /**
     * @brief Get the contents of the input box converted to the type T
     *        No type checking is done to make sure this works nicely
     */
    template<typename T>
    T get() const {
      Fl_Input* input = static_cast<Fl_Input*>(m_widget);
      std::istringstream is(input->value());
      T ret;
      is >> ret;
      return ret;
    }

    void reset() {
      Fl_Input* input = static_cast<Fl_Input*>(m_widget);
      input->cut(0,input->size());
      input->insert(m_label.c_str());
    }

  private:
    LabelBox *m_border; //!hack to put a white border around the box to make it look right
  };

  /**
   * @class Output
   * @author ngrau@augie.edu
   * @date Fall 2024
   * @brief A single line of text as an output. 
   *        Looks like an input box but you cannot type in it.
   */
  class Output : public Widget {
  public:

    /**
     * @brief Construct an Output object with an upper left point, a width, a height, and a default text
     */
    Output(const Point& p, int width, int height, const Text& defaultText) : Widget(p,width,height,defaultText,nullptr) {
      setFillColor(Color::WHITE);
    }

    /**
     * @brief Override Widget::attach() to attach this output text box to the window
     */
    void attach(Window* w){
      m_owner = w;
      Fl_Output *output = new Fl_Output(m_point.x,m_point.y,m_width,m_height,"");
      output->static_value(m_label.c_str());
      m_widget = output;
      m_widget->color(fillColor(),fillColor());
    }

    /**
     * @brief Put the following data with type T onto the output
     */
    template<typename T>
    void put(T data){
      Fl_Output* output = static_cast<Fl_Output*>(m_widget);
      std::ostringstream ss;
      ss << data;
      output->value(ss.str().c_str());
    }

    void reset() {
      Fl_Output* output = static_cast<Fl_Output*>(m_widget);
      output->cut(0,output->size());
      output->insert(m_label.c_str());
    }
};

  /**
   * @class MenuItem
   * @author ngrau@augie.edu
   * @date Fall 2024
   * @brief Wrapper class around the Fl_Menu_Item struct
   */
  class MenuItem {
  public:

    /**
     * @brief MenuItemFlags_t
     * @brief Enumeration to give names to the flags of a MenuItem
     *        These represent bits and therefore these flags can be  bitwise-OR'd 
     *        together. For example and inactive radio item would have a flag 
     *        INACTIVE | RADIO
     */
    enum MenuItemFlags_t {
      INACTIVE = FL_MENU_INACTIVE, //!if the menu item was not clickable
      TOGGLE = FL_MENU_TOGGLE, //!if is a checkbox item
      VALUE = FL_MENU_VALUE, //! on/off state for checkbox or radio buttons
      RADIO = FL_MENU_RADIO, //! item is a radio button
      INVISIBLE = FL_MENU_INVISIBLE, //! item will not show in the menu (shortcut will work)
      SUBMENU = FL_SUBMENU, //! item is a submenu for other items
      DIVIDER = FL_MENU_DIVIDER //! creates a divider line after the item, or ends a group of radio buttons
    };

    /**
     * @brief construct a MenuItem from the character string that it will display, 
     *        a callback function that will be invoked when the menu item is chosen, 
     *        any addition data that will be passed to the callback, and an integer 
     *        flags (see above)
     */
    MenuItem(const char* text=0, Callback_t callback=nullptr, Address_t userData=nullptr, int flags=0) : m_item({text,0,reinterpret_cast<Fl_Callback*>(callback),userData,flags}) {}

    /**
     * @brief retrieve this object as an Fl_Menu_Item object
     */
    Fl_Menu_Item get() const { return  m_item; }
      
  private:
    Fl_Menu_Item m_item; //!FLTK menu item structure {text,key shortcut,callback,userData,flags,labeltype,labelfont,labelsize,labelcolor}
  };

  /**
   * @class DropdownMenu
   * @author ngrau@augie.edu
   * @date Fall 2024
   * @brief A dropdown menu composed of several MenuItems
   */
  class DropdownMenu : public Widget {
  public:

    /**
     * @brief Construct a DropdownMenu with a upperleft point, width, height, and vector of MenuItems.
     */
    DropdownMenu(const Point& p, int width, int height) : Widget(p,width,height,{""},nullptr), m_items() {
    }

    /**
     * @brief Destructor
     */
    virtual ~DropdownMenu() {
      delete[] m_items_ptr;
    }

    /**
     * @brief add an item to the menu
     */
    void add(const MenuItem& item){
      m_items.push_back(item);
    }

    /**
     * @brief Override Widget::attach() to attach this menu to the window
     */
    void attach(Window *window){
      m_owner = window;
      Fl_Choice *menu = new Fl_Choice(x(),y(),w(),h());
      m_items_ptr = new Fl_Menu_Item[m_items.size()];
      for(size_t i=0; i<m_items.size(); ++i){
	m_items_ptr[i] = m_items[i].get();
      }
      menu->copy(m_items_ptr);
      m_widget = menu;
    }

    /**
     * Return the index of the menu item list that was chosen.
     */
    int value() const {
      return static_cast<Fl_Choice*>(m_widget)->value();
    }

    /**
     * @brief Make the menu be at a particular index of the menu item list
     */
    void value(int index) {
      static_cast<Fl_Choice*>(m_widget)->value(index);
    }
    
  private:
    std::vector<MenuItem> m_items; //!the list of menu items of this menu
    Fl_Menu_Item* m_items_ptr; //the pointer to the FLTK menu items
  };

  /**
   * @class MenuBar
   * @author ngrau@augie.edu
   * @date Fall 2024
   * @brief A MenuBar with several submenus
   *
   *        Create a MenuBar with just an upperleft point, a width, and a height
   *        The create a submenu that in the order they will appear left to right
   *        on the window using addMenu(const std::string& menuTitle)
   *        Then for each submenu, you can add individual MenuItems using
   *        addMenuItem(const std::string& menuTitle, const MenuItem& item)
   *        Again, order matters. Finally after the submenus and items have been
   *        added, only then should you attach(Window *window).
   *        
   */
  class MenuBar : public Widget {
  public:

    /**
     * @brief Construct a MenuBar with a point, a width, and a height
     */
    MenuBar(const Point& p, int width, int height) : Widget(p,width,height,{""},nullptr), m_menuOrder(), m_items(), m_items_ptr() {}

    /**
     * @brief Destructor
     */
    virtual ~MenuBar(){
      for(auto &e : m_items){
	for(auto &i : e.second){
	  delete i;
	}
      }
      delete[] m_items_ptr;
    }

    /**
     * @brief Add a new submenu to the MenuBar
     *
     *        This must first be called with the title before
     *        adding items to the submenu. The order of multiple
     *        calls to this method will result in several 
     *        submenus created left-to-right in the order the
     *        method was called.
     */
    void addMenu(const std::string& menuTitle) {
      m_menuOrder.push_back(menuTitle);
      m_items[menuTitle] = std::vector<MenuItem*>();
    }

    /**
     * @brief Add a MenuItem item to a submenu menuTitle
     *
     *        Call only after the addMenu is called to establish 
     *        the submenu. The order this method is called for
     *        a specific submenu determines the top-to-bottom order
     *        of the items in the submenu
     */
    void addMenuItem(const std::string& menuTitle, const MenuItem& item){
      m_items[menuTitle].push_back(new MenuItem(item));
    }

    /**
     * @brief Overrides Widget::attach(Window*) to attach the MenuBar to the window
     */
    void attach(Window *window){
      m_owner = window;
      Fl_Menu_Bar *menu = new Fl_Menu_Bar(x(),y(),w(),h());
      //count the number of total menu items
      size_t nitems = 0;
      for(auto &s : m_items){
	//it is two more than the number of menu items per sub menu
	nitems += s.second.size()+2;
      }
      //and then we need to add one more
      nitems++;

      //the whole set of menu items are stored as a fixed-length array
      m_items_ptr = new Fl_Menu_Item[nitems];
      size_t index = 0;
      for(auto &s : m_menuOrder){
	//indicate the start of the submenu
	m_items_ptr[index] = {s.c_str(),0,nullptr,0,FL_SUBMENU};
	index++;
	//now add the itmes of the submenu
	for(auto &i : m_items[s]) {
	  m_items_ptr[index] = i->get();
	  index++;
	}
	//end the submenu
	m_items_ptr[index] = {0};
	index++;
      }
      //indicate the end of all submenus
      m_items_ptr[index] = {0};
      menu->copy(m_items_ptr);
      m_widget = menu;
    }

  private:
    std::vector<std::string> m_menuOrder; //! the order of menus in the menu bar
    std::map<std::string,std::vector<MenuItem*> > m_items; //!the several different items
    Fl_Menu_Item* m_items_ptr; //!the pointer to the FLTK menu items
  };

}

#endif /* GUI_HH__ */
