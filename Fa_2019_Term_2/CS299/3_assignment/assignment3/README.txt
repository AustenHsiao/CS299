For assignment 3 in CS299, written by Austen Hsiao

The biggest issue in my program is that there is no function that handles reading in songs from a text file-- the code sits in main.cpp.
The file reading code is also entirely dependent on how the text file is written and it MUST be in the form

<Song title>
<Song artist>
<Album name>
<Song length>

otherwise it will not load in. Jordan helped in the implementation in which the song and the nodes of the BST
have been separated (2 nodes). Originally, my nodes directly contained fields for song name, artist, etc. but with this
style of abstraction, it was much easier to maintain since 'song' types only handle information pertinent to 
songs. Thanks, Jordan. 

I googled ASCII art, here's what I found:

      .-.
     (o.o)
      |=|
     __|__
   //.=|=.\\
  // .=|=. \\
  \\ .=|=. //
   \\(_=_)//
    (:| |:)
     || ||
     () ()
     || ||
     || ||
l42 ==' '==

Happy Halloween!

Austen Hsiao
