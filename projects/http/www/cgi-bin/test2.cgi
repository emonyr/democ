#!/bin/sh
echo Content-type: text/html
echo
echo "<HTML><HEAD>"
echo "<TITLE>Echo current time</TITLE>"
echo "</HEAD><BODY>"
echo "<p>Today is</p>"
date
echo "<p></p>"
echo "</BODY></HTML>"