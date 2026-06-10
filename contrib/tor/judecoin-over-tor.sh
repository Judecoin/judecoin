diff --git a/contrib/tor/jude-over-tor.sh b/contrib/tor/jude-over-tor.sh
index b0c711b..fix
--- a/contrib/tor/jude-over-tor.sh
+++ b/contrib/tor/jude-over-tor.sh
@@ -4,28 +4,28 @@
 
 DIR=$(realpath $(dirname $0))
 
-echo "Checking juded..."
-juded=""
+echo "Checking judecoind..."
+judecoind=""
 for dir in \
   . \
   "$DIR" \
   "$DIR/../.." \
   "$DIR/build/release/bin" \
   "$DIR/../../build/release/bin" \
   "$DIR/build/Linux/master/release/bin" \
   "$DIR/../../build/Linux/master/release/bin" \
   "$DIR/build/Windows/master/release/bin" \
   "$DIR/../../build/Windows/master/release/bin"
 do
-  if test -x "$dir/juded"
+  if test -x "$dir/judecoind"
   then
-    juded="$dir/juded"
+    judecoind="$dir/judecoind"
     break
   fi
 done
-if test -z "$juded"
+if test -z "$judecoind"
 then
-  echo "juded not found"
+  echo "judecoind not found"
   exit 1
 fi
-echo "Found: $juded"
+echo "Found: $judecoind"
@@ -66,18 +66,18 @@
 fi
 
-echo "Starting juded..."
+echo "Starting judecoind..."
 HOSTNAME=$(cat "$HOSTNAMEFILE")
-"$juded" \
+"$judecoind" \
   --anonymous-inbound "$HOSTNAME":18083,127.0.0.1:18083,25 --tx-proxy tor,127.0.0.1:9050,10 \
   --add-priority-node zbjkbsxc5munw3qusl7j2hpcmikhqocdf4pqhnhtpzw5nt5jrmofptid.onion:18083 \
   --add-priority-node 2judenode5itf65lz.onion:18083 \
   --detach
 ready=0
 for i in `seq 10`
 do
   sleep 1
-  status=$("$juded" status)
+  status=$("$judecoind" status)
   echo "$status" | grep -q "Height:"
   if test $? = 0
   then
@@ -87,7 +87,7 @@
 fi
 if test "$ready" = 0
 then
-  echo "Error starting juded"
+  echo "Error starting judecoind"
   tail -n 400 "$HOME/.bitjude/bitjude.log" | grep -Ev stacktrace\|"Error: Couldn't connect to daemon:"\|"src/daemon/main.cpp:.*Jude\ \'" | tail -n 20
   exit 1
 fi
