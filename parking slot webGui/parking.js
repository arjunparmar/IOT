const firebaseConfig = {
    apiKey: "AIzaSyDqtFTh9Z43MBWuAMS8lY4ylIFQyzf5fcw",
    authDomain: "iot-project-481fb.firebaseapp.com",
    databaseURL: "https://iot-project-481fb.firebaseio.com",
    projectId: "iot-project-481fb",
    storageBucket: "iot-project-481fb.appspot.com",
    messagingSenderId: "474970753176",
    appId: "1:474970753176:web:09549c6f49001769"
  };

  firebase.initializeApp(firebaseConfig);

  $(document).ready(function()
  {
    var database = firebase.database();
    
     database.ref().on('value',async (snap)=>{
         slot1 = await snap.val().slot1;
         slot2 = await snap.val().slot2;
         slot3 = await snap.val().slot3;
         slot4 = await snap.val().slot4;
         console.log(slot1,slot2,slot3,slot4)

         if(slot1===1)
            { 
                $("#00").text("slot occupied");              
                 $('#car00').show(1000,function(){
                console.log("slot occupied");
                });
            }

              else
            {
                $("#00").text("slot unoccupied");                
                $('#car00').hide(1000,function(){
                    console.log("slot unoccupied");
                });
            }
            if(slot2===1)
            { 
                $("#01").text("slot occupied");              
                 $('#car01').show(1000,function(){
                console.log("slot occupied");
                });
            }

              else
            {
                $("#01").text("slot unoccupied");                
                $('#car01').hide(1000,function(){
                    console.log("slot unoccupied");
                });
            }
            if(slot3===1)
            { 
                $("#10").text("slot occupied");              
                 $('#car10').show(1000,function(){
                console.log("slot occupied");
                });
            }

              else
            {
                $("#10").text("slot unoccupied");                
                $('#car10').hide(1000,function(){
                    console.log("slot unoccupied");
                });
            }
            if(slot4===1)
            { 
                $("#11").text("slot occupied");              
                 $('#car11').show(1000,function(){
                console.log("slot occupied");
                });
            }

              else
            {
                $("#11").text("slot unoccupied");                
                $('#car11').hide(1000,function(){
                    console.log("slot unoccupied");
                });
            }



        });

    });