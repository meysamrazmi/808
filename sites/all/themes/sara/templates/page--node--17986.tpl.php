<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8" />
    <title>Vue Js Intro</title>
    <script src="http://civil808.com/sites/all/themes/sara/js/vue.js"></script>
    <script src="https://unpkg.com/vue-lazyload/vue-lazyload.js"></script>
</head>

<div id="app"></div>
<script>

    const app = new Vue({
        el:'#app',
        data:{
            inputBox:'',
            email_list:[],
            show:{}
        },
        mounted(){
            
        },
        methods: {
            addEmail() {

                /*this.$http.post(
                    'http://civil808.com/latin/pbd/insert_mail',
                    {"email" : "xx@mail.com"}
                    {
                    headers: {
                        'Accept': 'application/json'
                    }
                });
                
                this.$http.post('http://civil808.com/latin/pbd/insert_mail', {"email" : "xx@mail.com"} , {emulateJSON:true}).then(function(res){
                    console.log(res);
                });*/

                xhttp.open("POST", "http://civil808.com/latin/pbd/insert_mail", true);
                xhttp.setRequestHeader("Content-type", "application/json");
                xhttp.send("{'email' : 'xx@mail.com'}");

                /*this.email_list.push(this.inputBox);
                this.inputBox = '';
                var email = 'email';
                var emails = {};
                if( this.email_list.length > 10 ){
                   emails.email = this.email_list;
                   this.email_list = [];
                }
                this.show = emails;*/
            }
        },
        template:`
            <div id="app">
                <input @keyup.enter="addEmail" v-model="inputBox" place-holder="Submit Your Email..." autofocus="autofocus"  autocomplete="off"></input>
                <div>{{email_list}}</div><br/><br/><br/>
                <div>{{this.show}}</div>
            </div>
        `
    })

    /*const app = new Vue({
        el:'#app',
        data: {
            newss:[]
        },
        mounted() {
            fetch("http://civil808.com/android/all_user")
                .then(response => response.json())
                .then((data) => {
                    this.newss = data;
                })
        },
        filters: {
            converturl: function(value){
                if (!value) return '';
                var thestart = 'http://civil808.com/sites/default/files/styles/200x200/public';
                var theend = value.substr(8);
                return thestart + theend;
            }
        },
        template: `
            <div id="app">
                <li v-for="news in newss">
                    <span>{{news.name}}</span>
                    <img v-bind:src="news.picture | converturl" width="100px" height="100px"/>
                </li>
            </div>
        `
    })*/
</script>


<style>
    #app{
        margin:200px;
    }
</style>
<!--<body>
    <div id="app">
        <input v-model="message"></br>
        {{ message }}
        </br>
        <ul>
            <li v-for="food in food_items" >{{ food }}</li>
        </ul>
        <button v-on:click="buttonclicks">Click me!</button>

        <friend-component v-for="item in friends" v-bind:friend="item" />

    </div>

    <script>
    Vue.config.devtools = true;

    Vue.component('friend-component',{
        props:['friend'],
        filters: {
            ageInOneYear(age){
                return age + 1;
            },
            fullName(value){
                return `${value.last} , ${value.first}`;
            }
        },
        methods: {
            decrementAgeFriend(friend){
                friend.age = friend.age - 1;
            },
            incrementAgeFriend(friend){
                friend.age = friend.age + 1;
            }

        },
        template: `
            <div>
                <h4>{{ friend | fullName }}</h4>
                <h5>age = {{friend.age}}</h5>
                <button v-on:click="decrementAgeFriend(friend)"> - </button>
                <button v-on:click="incrementAgeFriend(friend)"> + </button>
                <input v-model="friend.first"/>
                <input v-model="friend.last"/>
            </div>
            `   
    });

    new Vue({
        el: '#app',
        data: {
            'message':'Hello World',
            'food_items':['hamburger','fries','rice'],
            friends:[
                {
                    first:'bobby',
                    last:'bob',
                    age:25
                },
                {
                    first:'bob',
                    last:'ros',
                    age:35
                }
            ]
        },
        methods:{
            buttonclicks: function(){
                alert('Hey! I was clicked!');
            }
        }
    });

    </script>

    
</body>-->
</html>
