#!/bin/sh

help() {
cat << __EOF

  binaries:

    /usr/bin/picocom
    /usr/bin/ascii-xfr

  packages:

    /var/lib/dpkg/info/picocom.list:/usr/bin/picocom
    /var/lib/dpkg/info/minicom.list:/usr/bin/ascii-xfr
__EOF
}

if [ $# -lt 1 ]; then
    echo "Not enough arguments"
    echo "Use:  ./cf_picocom.sh /dev/ttyACM0"
    exit 1
fi

if [ $1 = "-help" ] || [ $1 = "--help" ]; then
    help
    exit 0
fi

echo "NON-STANDARD escape char is the backslash, not the usual Control+A"
echo "Control \, Control Q to quit"
echo "Control \, Control S to send a file from the local directory"

# WORKS FEB 11 2021:
picocom -e \\ -f n -p n -d 8 -b 115200 --omap delbs,crlf --send-cmd "ascii-xfr -sn -l 50 -c 5" ${1}

exit 0

cat << __EOF
<map> is a comma-separated list of one or more of:
  crlf : map CR --> LF
  crcrlf : map CR --> CR + LF
  igncr : ignore CR
  lfcr : map LF --> CR
  lfcrlf : map LF --> CR + LF
  ignlf : ignore LF
  bsdel : map BS --> DEL
  delbs : map DEL --> BS
  spchex : map special chars (excl. CR, LF & TAB) --> hex
  tabhex : map TAB --> hex
  crhex : map CR --> hex
  lfhex : map LF --> hex
  8bithex : map 8-bit chars --> hex
  nrmhex : map normal ascii chars --> hex
<?> indicates the equivalent short option.
Short options are prefixed by "-" instead of by "--".

__EOF

# end
