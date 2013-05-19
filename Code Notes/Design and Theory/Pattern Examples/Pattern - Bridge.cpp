///////////////////////////////////////////////////////////////////////////////////////////////////////
//BRIDGE PATTERN
///////////////////////////////////////////////////////////////////////////////////////////////////////
/*-------------------------------------------------------------------------------------------
TYPE: Structural
USE: Creates a bridge between a class and different ways of using that class
     Eg. Different ways of rendering (OpenGL,DirectX...)
     Eg. Different ways of sending a message (Email, SMS, MSN...)
-------------------------------------------------------------------------------------------*/

class BridgeBase
{
public:
    virtual void BeginRender() = 0;
    virtual void EndRender() = 0;
};
class OpenGL : public BridgeBase
{
public:
    virtual void BeginRender();
    virtual void EndRender();
};
class DirectX : public BridgeBase
{
public:
    virtual void BeginRender();
    virtual void EndRender();
};

class Renderer
{
public:

    BridgeBase* renderer;

    void InitialiseRenderer(int rendererType)
    {
        //choose which renderer to use
        switch(rendererType)
        {
        case OPENGL:
            renderer = new OpenGL();
            break;
        case DIRECTX:
            renderer = new DirectX();
            break;
        }
    }

    void BeginRender() { renderer->BeginRender(); }
    void EndRender() { renderer->EndRender(); }
}