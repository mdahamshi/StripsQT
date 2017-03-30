# StripsQT
<h1>AI Homework 2 , Strips algorithm. </h1>

The Algorithm is written in C++ 
We used <b>Qt creator</b> to build the GUI, with <b>Qt Quick 2</b> (qml) 
We used two heuristic for the strips algorithm , the first is with general actions like: Move through first door, Move through second door , which translate to small actions (operators) like Move left , Move right ..
<br/><br/>
The second heuristic try every basic operator like Move left , Move right , Rotate left ..
<br/><br/>
Each action has his preconditions which he must satisfy to be done, also the action save a list of goals predicates and another list of deleted predicates (the clear place he make after performing it and the place he occupied).
<br/><br/>
Most of the game logic and the heuristic are in <a href="https://github.com/mdahamshi/StripsQT/blob/withoutCout/src/broker.cpp">Broker.cpp</a>  and <a href="https://github.com/mdahamshi/StripsQT/blob/withoutCout/src/functions.cpp">functions.cpp</a>. All the C++ <b>source</b> is here : <a href="https://github.com/mdahamshi/StripsQT/tree/withoutCout/src">source</a>.
<br/><br/>
You can contact me if you got stucked or need any help at: <a href="mailto:mmd.0@hotmail.com?Subject=AI%20Project" target="_top"> mmd.0@hotmail.com</a>.
<br/> 
Thank you and good luck. 
<br/><br/>
You can <b>download</b> a portable version and test it from here : <a href="https://github.com/mdahamshi/StripsQT/raw/withoutCout/stripsQT.zip">StripsQT.zip</a>
<br/>
<br/><h2>Screenshots:</h2>
<br/>
![alt tag](https://github.com/mdahamshi/StripsQT/blob/master/screenshots/1.png)
![alt tag](https://github.com/mdahamshi/StripsQT/blob/master/screenshots/2.png)
![alt tag](https://github.com/mdahamshi/StripsQT/blob/master/screenshots/3.png)
![alt tag](https://github.com/mdahamshi/StripsQT/blob/master/screenshots/4.png)
![alt tag](https://github.com/mdahamshi/StripsQT/blob/master/screenshots/5.png)
![alt tag](https://github.com/mdahamshi/StripsQT/blob/master/screenshots/6.png)
<br/>
