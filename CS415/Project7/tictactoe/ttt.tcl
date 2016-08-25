# ttt.tcl



proc existence {variable} {
    upvar $variable testVar
    if { [info exists testVar] } {
        //puts "$variable Exists"
    } else {
       // puts "$variable Does Not Exist"
    }
}


variable soundFlag
set soundFlag ON







# Create canvas widget
canvas .c -width 300 -height 300 -bg white
.c create rectangle 0 0 100 100 -fill purple -outline black -width 10 -tags r1
.c bind r1 <Button-1> { if { [string equal [.t.13 cget -text] "Your Turn"] && [string equal [.c itemcget r1 -fill] "purple" ] }  {
	                      .c itemconfigure r1 -fill blue
                        puts stdout "1"
                        flush stdout
												
												if { [string equal [.t.16 cget -text] "X"] } { 
													  .c create line 0 0 100 100 -fill black -width 10
													  .c create line 0 100 100 0 -fill black -width 10
													} elseif { [string equal [.t.16 cget -text] "O"] } {
													.c create oval 0 0 100 100 -outline black -width 10
												} 
											  } else {
												  if { [string equal $soundFlag ON]  } { bell }
											  }
												}
.c create rectangle 100 0 200 100 -fill purple -outline black -width 10 -tags r2
.c bind r2 <Button-1> { if { [string equal [.t.13 cget -text] "Your Turn"] && [string equal [.c itemcget r2 -fill] "purple" ] }  {
	                      .c itemconfigure r2 -fill blue
                        puts stdout "2"
                        flush stdout
												
												if { [string equal [.t.16 cget -text] "X"] } { 
													  .c create line 100 0 200 100 -fill black -width 10
													  .c create line 100 100 200 0 -fill black -width 10
													} elseif { [string equal [.t.16 cget -text] "O"] } {
													.c create oval 100 0 200 100 -outline black -width 10
												}	
												} else {
													if { [string equal $soundFlag ON]  } { bell }
												}
												}
.c create rectangle 200 0 300 100 -fill purple -outline black -width 10 -tags r3
.c bind r3 <Button-1> { if { [string equal [.t.13 cget -text] "Your Turn"] && [string equal [.c itemcget r3 -fill] "purple" ] }  {
	                      .c itemconfigure r3 -fill blue
                       puts stdout "3"
                       flush stdout
											
												if { [string equal [.t.16 cget -text] "X"] } { 
													  .c create line 200 0 300 100 -fill black -width 10
													  .c create line 300 0 200 100 -fill black -width 10
													} elseif { [string equal [.t.16 cget -text] "O"] } {
													.c create oval 200 0 300 100 -outline black -width 10
												}
												} else {
													if { [string equal $soundFlag ON]  } { bell }
												}
												}
.c create rectangle 0 100 100 200 -fill purple -outline black -width 10 -tags r4
.c bind r4 <Button-1> { if { [string equal [.t.13 cget -text] "Your Turn"] && [string equal [.c itemcget r4 -fill] "purple" ] }  {
	                      .c itemconfigure r4 -fill blue
                       puts stdout "4"
                       flush stdout
												
												if { [string equal [.t.16 cget -text] "X"] } { 
													  .c create line 0 100 100 200 -fill black -width 10
													  .c create line 100 100 0 200 -fill black -width 10
													} elseif { [string equal [.t.16 cget -text] "O"] } {
													.c create oval 0 100 100 200 -outline black -width 10
												}
												} else {
													if { [string equal $soundFlag ON]  } { bell }
												}
 												}
.c create rectangle 100 100 200 200 -fill purple -outline black -width 10 -tags r5
.c bind r5 <Button-1> { if { [string equal [.t.13 cget -text] "Your Turn"] && [string equal [.c itemcget r5 -fill] "purple" ] }  {
	                      .c itemconfigure r5 -fill blue
                       puts stdout "5"
                       flush stdout
												 
												if { [string equal [.t.16 cget -text] "X"] } { 
													  .c create line 100 100 200 200 -fill black -width 10
													  .c create line 200 100 100 200 -fill black -width 10
													} elseif { [string equal [.t.16 cget -text] "O"] } {
													.c create oval 100 100 200 200 -outline black -width 10
												}
												} else {
													if { [string equal $soundFlag ON]  } { bell }
												}
												}
.c create rectangle 200 100 300 200 -fill purple -outline black -width 10 -tags r6
.c bind r6 <Button-1> { if { [string equal [.t.13 cget -text] "Your Turn"] && [string equal [.c itemcget r6 -fill] "purple" ] }  {
	                      .c itemconfigure r6 -fill blue
                       puts stdout "6"
                       flush stdout
												
												if { [string equal [.t.16 cget -text] "X"] } { 
													  .c create line 200 100 300 200 -fill black -width 10
													  .c create line 300 100 200 200 -fill black -width 10
													} elseif { [string equal [.t.16 cget -text] "O"] } {
													.c create oval 200 100 300 200 -outline black -width 10
												}	
												} else {
													if { [string equal $soundFlag ON]  } { bell }
												}
											}
.c create rectangle 0 200 100 300 -fill purple -outline black -width 10 -tags r7
.c bind r7 <Button-1> { if { [string equal [.t.13 cget -text] "Your Turn"] && [string equal [.c itemcget r7 -fill] "purple" ] }  {
	                      .c itemconfigure r7 -fill blue
                       puts stdout "7"
                       flush stdout
											 
												if { [string equal [.t.16 cget -text] "X"] } { 
													  .c create line 0 200 100 300 -fill black -width 10
													  .c create line 0 300 100 200 -fill black -width 10
													} elseif { [string equal [.t.16 cget -text] "O"] } {
													.c create oval 0 200 100 300 -outline black -width 10
												}
												} else {
													if { [string equal $soundFlag ON]  } { bell }
												}
											}
.c create rectangle 100 200 200 300 -fill purple -outline black -width 10 -tags r8
.c bind r8 <Button-1> { if { [string equal [.t.13 cget -text] "Your Turn"] && [string equal [.c itemcget r8 -fill] "purple" ] }  {
	                      .c itemconfigure r8 -fill blue
                       puts stdout "8"
                       flush stdout
									
												if { [string equal [.t.16 cget -text] "X"] } { 
													  .c create line 100 200 200 300 -fill black -width 10
													  .c create line 100 300 200 200 -fill black -width 10
													} elseif { [string equal [.t.16 cget -text] "O"] } {
													.c create oval 100 200 200 300 -outline black -width 10
												}
												} else {
													if { [string equal $soundFlag ON]  } { bell }
												}
											}
.c create rectangle 200 200 300 300 -fill purple -outline black -width 10 -tags r9
.c bind r9 <Button-1>  {if { [string equal [.t.13 cget -text] "Your Turn"] && [string equal [.c itemcget r9 -fill] "purple" ] }  {
	                      .c itemconfigure r9 -fill blue
                       puts stdout "9"
                       flush stdout
										
												if { [string equal [.t.16 cget -text] "X"] } { 
													  .c create line 200 200 300 300 -fill black -width 10
													  .c create line 200 300 300 200 -fill black -width 10
													} 
												if { [string equal [.t.16 cget -text] "O"] } {
													.c create oval 200 200 300 300 -outline black -width 10
												}
												 } else {
													if { [string equal $soundFlag ON]  } { bell }
												}
												}


pack .c -side top

# Frame to hold scrollbars
frame .t
pack  .t -expand 1 -fill x 


label .t.11 -text "Handle1 will go here"
label .t.12 -text "Opponent handle will go here"
label .t.13 -text "Status will go here"
label .t.14 -text " - "
label .t.15 -text " - "
label .t.16 -text "x or o"
label .t.17 -text "x or o"



grid .t.11 -row 0 -column 0
grid .t.12 -row 1 -column 0
grid .t.13 -row 0 -column 3
grid .t.14 -row 0 -column 1
grid .t.15 -row 1 -column 1
grid .t.16 -row 0 -column 2
grid .t.17 -row 1 -column 2



# Frame for holding buttons
frame .bf
pack  .bf -expand 1 -fill x

# Exit button
button .bf.exit -text "Exit" -command {
	if { [string equal [.t.13 cget -text] "You win!"] || [string equal [.t.13 cget -text] "You lose"] \
	|| [string equal [.t.13 cget -text] "Draw"] || [string equal [.t.13 cget -text] "Opponent Resigned"]
	} {
	exit}
  }

# Reset button
button .bf.sreset -text "Silent" -command \
    { 

	   if { [string equal $soundFlag  ON] } {
		   .bf.sreset configure -text "Sound"
       set soundFlag OFF     
      } elseif { [string equal $soundFlag  OFF] } {
	     set soundFlag ON
			 .bf.sreset configure -text "Silent"
	     
	     bell
      }
   }

# Dump PostScript
button  .bf.psout -text "Resign" -command \
    { if { [string equal [.t.13 cget -text] "Your Turn"] } {
		 puts stdout "xx"
     flush stdout
	   .t.13 configure -text "You lose"}
	  }

# Pack buttons into frame
pack .bf.exit .bf.sreset .bf.psout -side left \
    -expand 1 -fill x

#Call replot
#replot 0