/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VUE.JS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*************************************************************************************************************
• Vue.js is a Javascript framework for UI built on top of HTML, CSS, and JavaScript
• Built using npm (nvm needed for Windows) and packaged with vite
**************************************************************************************************************/

<!DOCTYPE html>
<head>
  <script src="https://unpkg.com/vue@3"></script>
</head>
<body>
  <div id="content" class="container">
    <!-- Template goes here -->
  </div>
  <script>
    Vue.createApp({
      computed: { // Properties computed dynamically
      },
      data() {
        return {
          myStr: "My String",
          myArr: ['One', 'Two'],
          myObjArr: [{ text: 'One', url: 'test.html' }]
        };
      },
      methods: {
         MyFun() { return 0; }
      }  
    }).mount('#content') // Mount in div element with id 'content'
  </script>
</body>
</html>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TEMPLATE
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

<h1>{{ myStr }}</h1>      // Access data property
<p>{{ myArr[0] }}</p>     // Access data array

// FOR-LOOP
<p v-for="arr in myArr">{{ arr }}</p> // For loop over array, creates multiple <p> elements
<p v-for="(arr, index) in myArr">{{ arr }}</p>

// IF-ELSE
<p v-if="value"></p>
<p v-else-if="fn()"></p>
<p v-else-if="value > 0"></p>
<p v-else></p>

// SHOW
<p v-show="value"></p>  // Hides an element when condition is false by setting the CSS 'display' property value to 'none'

// V-BINDING
<a v-bind:href="{{ myStr }}"></a>               // Use in attribute, 'v-bind' optional
<a :title="`This is some text ${myStr}`"></a>   // Use in attribute string, requires `

// CLASS BINDINGS
<a class="css-class"></a>                       // Default class to apply
<a :class="{'css-class2': !value}"></a>         // Bind class to change css for conditional expression, requires '' if name has -
<a :class="[`css-class${value}`]"></a>          // Change class based on variable
<a :class="[value ? 'css-class' : 'css-class2']"></a> 

// V-ON (EVENTS)
<a v-on:click="MyFunction()"></a>               // Vue event handling
<a @click="MyFunction()"></a>                   // Same as v-on:click
<a @click.prevent="MyFunction()"></a>           // Prevent default action when clicking (navigating to href)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// COMPONENTS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* MyComponent.vue */
<template>
  <div>
    <h2>{{ str }}</h2>
  </div>
</template>
<script>
export default {
  data() {
    return {
      str: 'str'
    }
  }
};
</script>
<style></style>

/* App.vue */
<div class="myClass">
  <MyComponent></MyComponent>
</div>

