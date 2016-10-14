////////////////////////////////////////////////////////////////////////////////////////////////////
//WEB DEVELOPMENT
////////////////////////////////////////////////////////////////////////////////////////////////////
/*

TCP/IP: Network protocol that the internet uses for exchange of packets
IP ADDRESS: Internet Protocol address, four-byte unique number for every computer connected to net
DOMAIN NAME SYSTEM: Translates domain names (web addresses) into IP addresses
CLIENT-SIDE SCRIPT: Javascript that runs on client computer in a static web site
SERVER-SIDE SCRIPT: ASP.NET, PHP, Ruby on Rails that run on a web server and create a dynamic web site

STATIC WEB SITE 
1) The browser sends the GET request to the server
2) When server receieves requirest searches for file of website requested
3) The Web server sends the file back to the browser inside the HTTP response. 

DYNAMIC WEB SITE
1) The browser sends the GET request to the server
2) The server recognizes an extension different from .html and reads the file
3) The server processes the file and runs any instructions it finds
4) Dynamically generated html is returned to the client

HYPERTEXT TRANSFER PROTOCOL (HTTP)
• Allows browsers to communicate with the web server
• Uses GET method when requesting a web page
• Uses POST method when sending data to be processed (ie. search, submit)

WEB SERVER
• Type of server for internet: Hosts websites, virtual directories, share information
• Responds to requests for files from web clients and logs activity
• Apache HTTP Server / Internet Information Services (IIS) most popular
• Default protocols supported are HTTP and HTTPS
• For each site, must have at least one application/virtual directory pair

WEB SERVER APPLICATION
• A group of files that delievers content over protocols
• Application becomes part of the site URL

WEB SERVICES
• Service that constantly runs on a web server which provides libraries other web applications can access
• Web applications access service through XML based (platform independent) protocols:
    - SOAP/REST: XML-based protocal used to exchange information over HTTP
    - WSDL: XML-based protocal used to describe capabilities and how to connect to service

*/
////////////////////////////////////////////////////////////////////////////////////////////////////
//HYPERTEXT MARKUP LANGUAGE (HTML)
////////////////////////////////////////////////////////////////////////////////////////////////////
// • Language browsers use to display webpages, Passed from webserver to client
// • Void element: cannot have content, requires no closing bracket (br, meta)

<!DOCTYPE HTML>
<html> //begin page
  <head>
    
    <title>My Title</title>
    <link href="favicon.ico" rel="icon" />
    <meta charset="utf-8"> // character set

  </head>
  <body>
    
    // ELEMENTS
    // • Uses the CSS from the class
    // • access element via 'this.property'
    // • has a unique ID, must be unique
    // • can set properties also through style
    // • Can use single ' or double quotes " for properties
    <MyElement class ="MyCustomClass" id = "MyID" style="visibility: hidden;"</MyElement>
    <div></div>         // Container
    <span></span>       // Formatting section
    <section></section> // Page divisions
    <article></article> // Section of the page that contains the main content
    <aside></aside>     // Quotation, advertisement, sidebar
    
    // LINKS
    <a href="mypage.html">MyLink</a>                       // Add Global styled Link to text
    <a href="mypage.html" class ="MyClass">MyLink</a>      // Add Class styled Link to text
    <a href="myPage.html" target="_blank">Open window</a>  // Open popup window

    // IMAGES
    <img src="/images/logo.jpg" height="50px" width="200px" border="0" alt="MyText"/>
    <img src="myImage1.jpg" width="290" height="30" onmouseover="this.src='myImage1.jpg'" onmouseout="this.src='myImage2.jpg'" />

    // TABLES
    <table id="myTable" width="300" height="500" border="0" cellpadding="5">
      <tr>
        <td></td>
      </tr>
    </table>
    
    // MULTIMEDIA
    <video src="myvideo.mp4" width="550" height="400"></video>
    <audio src="mysong.mp3" controls="controls"></audio>
    <button>My Button</button>

    // TEXT
    <sup></sup>       // superscript text:ᵃ
    <sub></sub>       // subscript text:ₐ
    <code></code>     // computer code
    <p></p>           // paragraph
    <strong></strong> // Bold 
    <em></em>         // Italic
    <small></small>   // small print
    <br />            // Newline, void element
    &nbsp;            // Space    
    
    // EVENTS
    <div onload="MyFunction()"></div>
    onabort       // interruption of image loading
    onblur        // element loses focus
    onchange      // change of data inside an element
    onclick       // element is clicked
    ondblclick    // element is double clicked
    onerror       // when error in script or when loading image
    onfocus       // when element gets focus
    onkeydown     // pressing a key on keyboard
    onkeypress    // pressing and releasing a key on the keyboard
    onkeyup       // releasing a key on the keyboard
    onload        // end of loading of element or image
    onmousedown   // pressing mouse button
    onmouseout    // mouse leaving element area
    onmouseover   // mouse entering element area
    onmouseup     // releasing mouse button
    onmove        // window/frame moving
    onresize      // changing size of window/frame
    onselect      // selecting text
    onunload      // leaving the page or closing the window
    
  </body>
  <footer>
  </footer>
</html>

////////////////////////////////////////////////////////////////////////////////////////////////////
//CASCADING STYLE SHEETS (CSS)
////////////////////////////////////////////////////////////////////////////////////////////////////

// INLINE STYLING: Add CSS to individual elements within style attribute
<div class ="MyCustomClass"></div>

// EXTERNAL STYLE: Uses <link> to connect to extenal .CSS
<link rel="stylesheet" type="text/css" href="resumestyle.css" />

// PAGE-LEVEL STYLE: Add CSS to entire page using <style> tag
<style type="text/css"> div { font-family: Verdana; } </style>

.MyCustomClass
{
  width: 888px;
  height: 25px;
  visibility: hidden; // visible
  cursor: crosshair;
  opacity: 1.0;

  font-family: Verdana, Geneva, sans-serif;
  font-size: 9pt;
  font-style: normal; // italic
  font-variant: normal;
  font-weight: bold;  
  line-height: 1;  
  text-align: right; // center,left
  text-transform: capitalize;
  text-decoration: underline;
 
  background-repeat: repeat-y; // no-repeat,repeat-x
  background: #939393;
  background-position: right top;
  background-image: url("MyBground.PNG"); 
  background-attachment: fixed; // fix bground to page

  border: none;
  border-style: solid;
  border-width: 1px;
  border-color: #939393;
  border-radius: 4px; // creates rounded corners
  box-shadow: 5px 5px gray; // create drop shadow

  margin: 0;
  margin-top: 0;
  margin-right: auto;
  margin-bottom: 0px;
  margin-left: auto;  
  
  padding: 0;
  padding-right: 0px;
  padding-left: 0px;  
  
  scrollbar-3dlight-color: #FFD700; 
  scrollbar-arrow-color: #FFFF00;
  scrollbar-base-color: #FF6347;
  scrollbar-darkshadow-color: #FFA500;
  scrollbar-face-color: #FF5522;
  scrollbar-highlight-color: #FF69B4;
  scrollbar-shadow-color: #FF00FF;
  scrollbar-track-color: #FFAA22; 
}

// VERTICAL TEXT ALIGN
#parent {display: table;}
#child { display: table-cell; vertical-align: middle; }

// CLASSES
// comma for multiple classes or else seen as contextual selector
.MyClass, div
{ 
    property:value; //declaration
}

//PSEUDO CLASS
//elementSelector:pseudoclass
a               { color: #e8e8eb; text-decoration: none; } // all links
a:link          { color: #e8e8eb; text-decoration: none; }
a:visited       { color: #e8e8eb; text-decoration: none; }
a:hover         { color: #e8e8eb; text-decoration: none; }
a:active        { color: #e8e8eb; text-decoration: none; }
a:focus         { color: #e8e8eb; text-decoration: none; }
a.MyClass:link  { color: #e8e8eb; text-decoration: none; }
a img           { border: none; }

// CONTEXTUAL SELECTORS
// will only occur when <MyParent><MyChild>Testing</MyChild></MyParent>
.MyParent .MyChild { }

// UNIVERSAL SELECTORS
// Apply properties to all elements
* { }

// ELEMENT CLASSES
// Only be applied to a div <div class="MyClass"></div> and not a <span>
div.MyClass { }

// ID CLASSES
// Only be applied to HTML elements with an id <div id="MyID"></div>
// ID cannot start with number, cannot use symbols
#MyID { }

// CASCADING PROPERTY
// Properties are kept and overwritten if needed
<MyParent><MyChild>MyBold12Text</MyChild><MyParent> // will retain bold property
.MyParent { font-size: 48px; font-weight: bold; }
.MyChild { font-size: 12px; }

////////////////////////////////////////////////////////////////////////////////////////////////////
//JAVASCRIPT
////////////////////////////////////////////////////////////////////////////////////////////////////
//• Can be used in header/body or inside links/elements
//• When inside <script></script> tags use " for string otherwise use '
//• Variables don't use same name as element ID

<script>...</script> // Inlining javascript
<script src="myscript.js"></script> // Loading a script file
<noscript>JavaScript is turned off</noscript> // only displayed if no support

<script type="text/javascript">
<a href="javascript:MyFunction('use commas for string')">MyLink</a>
<div onclick="MyFunction('Hello')"></div>
<b onclick="MyFunction('Hello');MyOtherFunction();">Some Bold Text</b>

// HTML DOCUMENT OBJECT MODEL (DOM)
// Views html as a tree, elements must be defined above script to be seen
screen.availWidth
screen.availHeight
document.bgColor = "#000000";
document.write("MyText<b>InBold</b>");    // Adds the text where the <script></script> is positioned
document.lastModified;                    // Text for when the page was last modified
document.title;                           // Title of the page
document.getElementById("MyElementID");   // Returns element by its ID or null if doesn't exist
document.getElementByName("MyElName");    // Returns element by its name or null if doesn't exist
document.getElementsByTagName("MyElTag"); // Returns element by its tag or null if doesn't exist
myElement.innerText                       // OR MyElementID.innerText
myElement.bgColor;                        // can read/write all properties of element
myElement.style.width;                    // access properties declared in <style></style> tags