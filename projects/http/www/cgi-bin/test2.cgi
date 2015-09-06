#!/bin/sh
echo Content-type: text/html
echo
echo "<HTML><HEAD>"
echo "<TITLE>Echo current time</TITLE>"
echo "</HEAD><BODY>"
echo "<p>Calendar</p>"
#cal | sed -i 's/\n/\r\n/g'
date
echo "<p></p>"
echo "</BODY></HTML>"