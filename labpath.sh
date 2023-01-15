#!/bin/bash
while true; do
  mysql --defaults-extra-file=~/.mysqlpwd quelle -e"DELETE FROM labpatel WHERE fertig=0";
  labpath;
done;
