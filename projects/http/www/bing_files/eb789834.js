var BM=BM||{};BM.config={B:{timeout:7e3,delay:750,maxUrlLength:300,sendlimit:20},S:{distance:20},N:{maxUrlLength:300},E:{buffer:30,timeout:5e3,maxUrlLength:300},C:{distance:50}};BM=BM||{};BM.rules={"#sc_hdu":[-1,-1,1],"#hp_id_hdr":[-1,-1,1],"#hp_container":[-1,-1,1],".hp_sw_logo":[-1,-1,0],".b_searchboxForm":[-1,-1,0],"#crs_pane":[-1,-1,0],"#sb_foot":[-1,-1,0],"#sh_rdiv":[-1,-1,0],"img,div[data-src]":[-1,-1,0],iframe:[-1,-1,0]},function(n){function at(){var n,c;if(!document.querySelector||!document.querySelectorAll){et({FN:"init",S:"QuerySelector"});return}b={};u=[];y=document.documentElement;k=document.body;it=1;tt=0;nt=0;f=[];e=0;o=!1;var a="innerWidth"in window?window.innerWidth:y.clientWidth,p="innerHeight"in window?window.innerHeight:y.clientHeight,d=window.pageXOffset||y.scrollLeft,g=window.pageYOffset||y.scrollTop;w=s(window,"devicePixelRatio")?window.devicePixelRatio:-1;w=t+w;v=s(window,"getComputedStyle")?parseInt(window.getComputedStyle(document.body)["font-size"]):-1;v=v>0?v:-1;n={t:r(),x:d,y:g,w:a,h:p,dw:k.clientWidth,dh:k.clientHeight,d:w,s:v};c=Math.floor(Math.random()*1e4).toString(36);i={P:{C:0,N:0,I:c,S:"T",M:t,T:0,K:t},V:[n],L:[]};l={V:ut(n),L:[]};vi();sj_be(window,"beforeunload",h,!1);sj_evt.bind("unload",h);sj_evt.bind("BMU",h)}function vt(n,i){var r,e,u;if(n.querySelectorAll)for(r in ct){var f=ct[r],o=f[0],s=f[1];for(r+=!f[2]?t:" >*",e=n.querySelectorAll(r),u=0;u<e.length;u++)pt(e[u],i,o,s)}}function fi(){return l.V}function rt(){return l.L||[]}function yt(n,t){var r={};for(var i in n)i.indexOf("_")!==0&&(i in t&&(n[i]!==t[i]||i==="i")?(r[i]=t[i],n[i]=t[i]):r[i]=null);return r}function ei(n){while(n&&n.hasAttribute&&n!==document.body){if(n.hasAttribute("data-bm"))return parseInt(n.getAttribute("data-bm"));n=n.parentElement}return null}function oi(n,t,i){var u,r;if(n){for(u=rt(),r=0;r<u.length;r++)if(n===u[r]._e)return u[r].i;return i&&vt(n,t),pt(n,t)}return null}function pt(n,t,r,u){var f=dt(n,t);if(!(f.x<0)&&!(f.y<0))return r&&(f._ex=r),u&&(f._ey=u),(n.tagName==="IMG"||n.tagName==="IFRAME")&&(f._s=ai(n)),f.i=l.L.length,n.setAttribute("data-bm",f.i),i.L.push(f),l.L.push(ut(f)),f.i}function ut(n){var i={};for(var t in n)n.hasOwnProperty(t)&&(i[t]=n[t]);return i}function ft(n,t,i){if(!o){et({FN:"snapshot",S:n});return}i=i||ti;t=t||!1;var r=gt()+i;ot(f,n)===-1&&f.push(n);t?(wt(),bt(t)):r>e&&(wt(),nt=sb_st(bt,i),e=r)}function et(n){var f={T:"CI.BoxModelError",FID:"CI",Name:ht,P:i&&"P"in i?d(i.P):t,TS:r()},u,e;for(u in n)f[u]=n[u];e=d(f);kt(e)}function wt(){e>0&&(sb_ct(nt),e=0)}function bt(n){var t,u;if(!o){et({FN:"send",S:f.join(c[1])});return}(it<=ri||n)&&(i.P.S=f.join(c[1]),i.P.M=yi(),t=r(),si(),i.P.T=r(),i.P.N=it++,i.P.C+=r()-t,u=li(i),i.P.C=0,kt(u),f=[],e=0)}function si(){for(var t,f,i=rt(),u=r(),n=0;n<i.length;n++)t=i[n],f=dt(t._e,u),hi(t,f,u);o&&st("compute")}function hi(n,t,r){for(var u,o=["x","y","w","h","z"],f={},s=!1,e=0;e<o.length;e++)u=o[e],n[u]!==t[u]&&(s=!0,f[u]=t[u]);s&&(f.i=n.i,f.t=r,i.L.push(yt(n,f)))}function kt(n){if(s(window,"Log2")&&Log2.LogEvent&&JSON)Log2.LogEvent("ClientInst",JSON.parse(n));else{var i=gt(),r="<E><T>Event.ClientInst<\/T><IG>"+_G.IG+"<\/IG><TS>"+i+"<\/TS><D><![CDATA[["+n.replace("]\]>","]]]\]><![CDATA[>")+"]]\]><\/D><\/E>",u="<ClientInstRequest><Events>"+r+"<\/Events><STS>"+i+"<\/STS><\/ClientInstRequest>",t=sj_gx();t.open("POST","/fd/ls/lsp.aspx",!0);t.setRequestHeader("Content-Type","text/xml");t.send(u)}sj_evt.fire("BM",n)}function d(n){var r=t,u,i;for(u in n)if(i=n[u],i!==t){var o=typeof i=="number",f='"',e=o||i.indexOf("{")===0?t:f;r+=f+u+f+":"+e+i+e+","}return"{"+(r.length>0?r.substr(0,r.length-1):t)+"}"}function ci(n){return n.tagName+(n.id?"#"+n.id:n.className?"."+n.className:t)}function li(n){function k(n,i){function v(n){return n.replace(ui,encodeURIComponent)}var h=!0,f=[],u,r,e,s,o,l,a;if(i=i||1,!("_c"in n)||i<=1){for(u in n)if(r=n[u],s=u.charCodeAt(0)>=65&&u.charCodeAt(0)<=90,s&&f.push(u),u.indexOf("_")===0)continue;else typeof r=="number"?(e=parseInt(r).toString(36),f.push(e),g(e)):typeof r=="string"?(e=v(r),f.push(e),g(e)):r==null?f.push(t):typeof r=="object"&&(o=k(r,i+1,u),(o&&o.length>0||s)&&f.push(o),h=!1);h&&(n._c=!0)}return l=c[i],a=f.join(p+l+p),a}function g(n){n.length>2&&(n in v&&ot(u,n)===-1?u.push(n):v[n]=1)}var nt=r(),v={},h={T:"CI.BoxModel",FID:"CI",Name:ht,P:t},e={},s,y,f,o,w,l,a;for(f in n)f!=="P"&&(s=k(n[f]),s&&s.length>0&&(e[f]=s.split(p)));y=u.slice(tt).join(c[1]);tt=u.length;i.P.K=y;for(f in e){for(o=0;o<e[f].length;o++)w=e[f][o],l=ot(u,w),l>=0&&(e[f][o]=p+l.toString(36));a=e[f].join(t);f in b&&b[f]===a||(h[f]=b[f]=a)}return i.P.C+=r()-nt,h.P=d(i.P),d(h)}function ot(n,t){for(var i=0;i<n.length;i++)if(n[i]===t)return i;return-1}function dt(n,i){var r={t:i,i:null,s:ci(n),k:t,x:0,y:0,w:n.offsetWidth,h:n.offsetHeight,z:0,_e:n,_s:t,_ex:-1,_ey:-1},f=n.querySelector("a[h]"),u;r.k=f?f.getAttribute("h"):t;s(r,"k")&&(r.k=r.k?r.k.substr(r.k.indexOf("=")+1):t,r.k=r.k&&r.k.indexOf("javascript")>=0?t:r.k);u=n;try{if(n.offsetParent)do r.x+=n.offsetLeft,r.y+=n.offsetTop;while(n=n.offsetParent)}catch(e){r.x=null;r.y=null}while(u!==k&&(u=u.parentElement))r.z++;return r}function ai(n){try{if(s(n,"src")&&n.src.indexOf("data")!==0)return n.src?n.src:t}catch(i){}return t}function r(){return lt?ni(performance.now()):new Date-window.si_ST}function gt(){return lt?ni(performance.now()+performance.timing.navigationStart):(new Date).getTime()}function s(n,t){return typeof n[t]!="undefined"}function ni(n){return n<-1?-1:parseInt(n)}function vi(){var n=r();o=!0;vt(document,n);st("load");ft("T",!1,ii);i.P.C+=r()-n}function h(){sj_ue(window,"beforeunload",h);sj_evt.unbind("unload",h);sj_evt.unbind("BMR",h);ft("U",!0);o=!1;st("unload")}function st(n){for(var t=0;t<a.length;t++)a[t][n](i)}function yi(){for(var t=[],n=0;n<a.length;n++)t.push(a[n].id);return t.join(c[1])}function pi(n){n.check()&&a.push(n)}function wi(){sj_evt.bind("onP1",at,!0);sj_evt.bind("ajax.postload",at,!0)}if(!_w.BM||!n.register){var ht="v2.7.2",t="",ct=n.rules,g=n.config["B"],ti=g.delay,ii=g.timeout,ri=g.sendlimit,lt=_w.performance&&performance.now&&performance.timing,p="@",c=["$","+","/",":",";"],ui=/([%$+\/:;"])/g,u,i,l,a=[],w,v,b,f,e,nt,tt,it,o,k,y;sb_st(wi,0);n.register=pi;n.snapshot=ft;n.observe=oi;n.match=ei;n.delta=yt;n.clone=ut;n.exists=s;n.viewport=fi;n.layout=rt;n.time=r}}(BM),function(n){function o(){return!0}function s(n){e=n;r=document.documentElement;sj_be(window,"scroll",f)}function f(){return t.push({t:n.time(),i:0,x:window.pageXOffset||r.scrollLeft,y:window.pageYOffset||r.scrollTop}),n.snapshot(i),!0}function h(n,t){var i=n.x-t.x,r=n.y-t.y;return i*i+r*r>u*u}function c(i){for(var r,f,e=t.length,o=n.viewport(),u=0;u<e;u++)r=t[u],(u===0||u===e-1||h(r,f))&&(i.V.push(n.delta(o,{t:r.t,x:r.x,y:r.y})),f=r);t=[]}function l(){sj_ue(window,"scroll",f)}var i="S",t=[],u=n.config[i].distance,r,e;n.register({id:i,check:o,load:s,compute:c,unload:l})}(BM),function(n){function u(){return!0}function f(n){i=n;sj_be(window,"resize",r)}function r(){var r=document.documentElement,u=n.viewport(),f="innerWidth"in window?window.innerWidth:r.clientWidth,e="innerHeight"in window?window.innerHeight:r.clientHeight;i.V.push(n.delta(u,{t:n.time(),w:f,h:e}));n.snapshot(t)}function e(){}function o(){sj_ue(window,"resize",r)}var t="R",i;n.register({id:t,check:u,load:f,compute:e,unload:o})}(BM),function(n){function s(){return u in document}function h(n){n[t]=[];i=n;sj_be(document,"visibilitychange",f,!1);sj_evt.bind("visibility",e);sj_evt.bind("peekexpand",o);sj_be(window,"beforeunload",r,!1);sj_evt.bind("unload",r);sj_evt.bind("BMU",r)}function r(){i[t].push({t:n.time(),s:"unloaded",o:"unload"});n.snapshot(t,!0)}function f(){var r=document[u];i[t].push({t:n.time(),s:r,o:"visibility"});n.snapshot(t,r==="unloaded")}function e(r){if(r.length>1){var u=r[1]?"visible":"hidden";i[t].push({t:n.time(),s:u,o:"cortana"});n.snapshot(t,u==="hidden")}}function o(){var r=document.documentElement,u=n.viewport(),f="innerWidth"in window?window.innerWidth:r.clientWidth,e="innerHeight"in window?window.innerHeight:r.clientHeight;i.V.push(n.delta(u,{t:n.time(),w:f,h:e}));i[t].push({t:n.time(),s:"peekexpand",o:"cortana"});n.snapshot(t,!1)}function c(){}function l(){sj_ue(document,"visibilitychange",f);sj_ue(window,"beforeunload",r);sj_evt.unbind("unload",r);sj_evt.unbind("visibility",e);sj_evt.unbind("peekexpand",o);sj_evt.unbind("BMU",r)}var t="PS",u="visibilityState",i;n.register({id:t,check:s,load:h,compute:c,unload:l})}(BM),function(n){function f(){return typeof MutationObserver!="undefined"}function e(n){u=n;var t=new MutationObserver(o);t&&t.observe(document.body,{childList:!0,subtree:!0})}function o(u){var o,c,f,h,e,l,a;if(t!==null){for(o=[],c=n.time(),f=0;f<u.length;f++)for(h=0;h<u[f].addedNodes.length;h++)e=u[f].addedNodes[h],l=e.tagName,s(e)&&(a=n.observe(e,c,!0),o.push(e.parentNode));o.length>0&&(i=o,n.snapshot(r))}}function s(n){var t=n.offsetWidth>=20||n.offsetHeight>=20,r=i.indexOf(n.parentNode)>=0;return t&&!r}function h(){}function c(){t&&t.disconnect();t=null;i=[]}var r="M",i=[],t,u;n.register({id:r,check:f,load:e,compute:h,unload:c})}(BM),function(n){function k(){return!0}function d(n){n[i]=[];c=n}function g(r){for(var w,d,g,nt=n.viewport().w,k=n.layout(),a=0;a<k.length;a++){var u=k[a],f=u._e,h=u._s,s=u._ex,b=u._ey,c=e;u.i===a&&(s=_G.RTL&&s>=0?nt-s-f.offsetWidth:s,s>=0&&!p(u.x,s)&&(c=u.k.length===0?y(f):c,r[i].push({t:n.time(),l:u.i,e:"X",v:Math.abs(u.x-s),m:c})),b>=0&&!p(u.y,b)&&(c=u.k.length===0?y(f):c,r[i].push({t:n.time(),l:u.i,e:"Y",v:Math.abs(u.y-b),m:c})),f.tagName!=="IMG"||!h||u.i in t||(w=n.exists(f,w)?f[w]:!0,d=n.exists(f,o)?f[o]>1:!0,w?d||(t[u.i]={_e:f,_s:h,_d:!0,_b:!1},v(a,h)):(t[u.i]={_e:f,_s:h,_d:!1,_b:!0},l(f,!0))),f.tagName!=="DIV"||!f.hasAttribute("data-src")||u.i in t||(h=f.getAttribute("data-src"),g=f.style.backgroundImage,g||(t[u.i]={_e:f,_s:h,_d:!1,_b:!1},l(f,!1))))}}function l(n,t){t&&(sj_be(n,"load",u),sj_be(n,"error",u));r||(r=sb_st(a,b))}function u(n){var t=window.event||n,i=sj_et(n);return a(t.type,i)}function a(i,f){var s=0,e,o,h;for(e in t)if(!t[e]._d&&(!f||t[e]._e===f)&&(o=t[e]._e,h=o.tagName==="IMG"?!o[w]||i&&i==="error":!o.style.backgroundImage,t[e]._b&&(sj_ue(o,"load",u),sj_ue(o,"error",u)),h&&(v(e,t[e]._s),s++),t[e]._d=!0,f))return;s>0&&n.snapshot("E");r=0}function v(t,r){c[i].push({t:n.time(),l:t,e:"S",v:404,m:r.substr(0,h)})}function y(n){var t=n.querySelector("a");return t&&t.href?t.href.substr(0,h):e}function p(n,t){return n>=t-s&&n<=t+s}function nt(){var i,n;for(i in t)n=t[i],n._b&&!n._d&&(sj_ue(n._e,"load",u),sj_ue(n._e,"error",u));r&&(sb_ct(r),r=0);t={}}var i="E",e="",w="complete",o="naturalWidth",f=n.config[i],s=f.buffer,h=f.maxUrlLength,b=f.timeout,r=0,t={},c;n.register({id:i,check:k,load:d,compute:g,unload:nt})}(BM),function(n){function l(){return _w.performance&&performance.now&&performance.getEntries}function a(n){n[t]=[];e[t]=[]}function v(i){var r,c,p,l,v,k;if(t in e){var it=i[t],f=e[t],ft=performance.timing,d=performance.getEntries();for(r=0;r<f.length;r++)c=f[r]._r,f[r].i==r&&c&&u(c.duration)!==f[r].d&&i.N.push(n.delta(f[r],{i:f[r].i,t:n.time(),d:u(c.duration)}));for(p=d.length,l=o;l<p;l++){var h=d[l],w=h.name,a=y(w);w.indexOf("format=json")>=0&&(s=h.startTime);var rt=u(h.startTime-s),ut=u(h.duration),g=null,nt=n.layout();for(v=0;v<nt.length;v++){var b=nt[v],et=b._e,tt=b._s;if(tt&&w===tt){g=b.i;break}}k={_r:h,t:rt,i:f.length,l:g,h:a[0],p:a[0].length===0?a[2]:a[1],s:h.initiatorType,d:ut};it.push(k);f.push(n.clone(k))}o=p}}function y(n){var s,a,u,l,t,e,v,o;return i.href=n,l=i.hostname,t=i.pathname,t=t.indexOf(r)===0?t.substr(1):t,e=i.search.toLowerCase(),v=l.length>0?t.substr(0,h):n.substr(0,h),e.length>0&&(s=e.indexOf("event."))>0&&(a=e.indexOf("&data"))>0?(t=e.substr(s,a-s).replace("event.",f),t==="clientinst"&&(o=c.exec(e.replace(/%22/g,'"')),o!=null&&o.length>1&&(t=o[1]))):t.indexOf("rms/")===0&&(u=t.split(r))&&u.length>1?t=u[1].replace("rms%20answers%20",f).replace(".source",f):(u=t.split(r))&&u.length>=2&&(t=u[u.length-2]+r+u[u.length-1]),[l,t,v]}function u(n){return n<-1?-1:parseInt(n)}function p(){}var t="N",o=0,s=0,h=n.config[t].maxUrlLength,i=document.createElement("A"),f="",r="/",c=/"name":"(.*?)"/,e={};n.register({id:t,check:l,load:a,compute:v,unload:p})}(BM),function(n){function c(){return!0}function l(n){n[t]=[];h=n;u=document.documentElement;i=[];r={};o(sj_be,s)}function o(n,t){for(var r,i=0;i<e.length;i++)r=e[i],n(document,window.navigator.pointerEnabled?r.replace("mouse","pointer"):r,t,!1)}function s(r){r=_w.event||r;var f=r.pointerType||r.type.indexOf("touch")==0&&"touch"||"mouse",e={_e:r.target,t:n.time(),l:null,e:r.type,p:f,b:n.exists(r,"button")?r.button:null,x:r.pageX||r.clientX+u.scrollLeft,y:r.pageY||r.clientY+u.scrollTop,s:n.exists(r,"buttons")?r.buttons:null};return i.push(e),n.snapshot(t),!0}function a(n,t){var i=n.x-t.x,r=n.y-t.y;return i*i+r*r>f*f}function v(u){var s=i.length,o,e,f;if(s>0){for(o=(t in r)?r[t]:null,e=0;e<s;e++)f=i[e],(e===0||e===s-1||f.e.indexOf("move")<0||a(f,o))&&(f.l=n.match(f._e),o===null?(o=r[t]=n.clone(f),u[t].push(f)):u[t].push(n.delta(o,f)));i=[]}}function y(){o(sj_ue,s)}var t="C",i=[],r={},f=n.config[t].distance,e=["click","mousedown","mouseup","touchstart","touchend","mousemove","touchmove"],u,h;n.register({id:t,check:c,load:l,compute:v,unload:y})}(BM),function(n){function e(){return!0}function o(n){n[t]=[];r=n;u(sj_be,f)}function u(n,t){for(var u,r=0;r<i.length;r++)u=i[r],n(document,u,t,!1)}function f(i){i=_w.event||i;var u=n.time();return r[t].push({t:u,l:n.observe(i.target,u),e:i.type,m:i.shiftKey<<1|i.ctrlKey<<2|i.altKey<<3|i.metaKey<<4|(i.repeat||0)<<5|(i.isComposing||0)<<6|(i.location||0)<<16,kc:i.keyCode,w:i.which,cc:i.charCode,k:encodeURIComponent(i.key),c:i.code}),n.snapshot(t),!0}function s(){}function h(){u(sj_ue,f)}var t="K",i=["keydown","keypress"],r;n.register({id:t,check:e,load:o,compute:s,unload:h})}(BM),function(n){function o(){return!0}function s(n){n[i]=[];e=n;r(sj_be,u);t=!0}function r(n,t){for(var r,i=0;i<f.length;i++)r=f[i],n(r==="resize"?window:document,window.navigator.pointerEnabled?r.replace("mouse","pointer"):r,t,!1)}function u(f){if(t){f=_w.event||f;var o=""+Math.round((new Date).getTime()/1e3);e[i].push({t:n.time(),e:f.type,s:o});sj_cook.set("_SS","HV",o,!1,"/");t=!1;r(sj_ue,u);n.snapshot(i)}return!0}function h(){}function c(){t&&(r(sj_ue,u),t=!1)}var i="BD",f=["click","mousedown","mouseup","touchstart","touchend","mousemove","touchmove","scroll","keydown","resize"],e,t=!1;n.register({id:i,check:o,load:s,compute:h,unload:c})}(BM)