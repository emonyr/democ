var wln=wln||"";(function(){function n(n){n.style.display="none"}function t(n){n.style.display="inline-block"}if(sj_evt&&Identity){var i=function(){var u=_ge("id_n"),r=_ge("id_p"),e=_ge("id_s"),o=_ge("id_a"),s=_ge("id_f"),f=Identity.fbProfile()||Identity.wlProfile(),i=f?f.displayName:wln,h=f?f.img:null,c=f?f.idp:null;u&&e&&o&&i?(r&&h&&(r.title=i,r.src=h,t(r)),i.length>10&&(i=i.substring(0,10).replace(/\s+$/,"")+"…"),s&&s.innerText&&s.innerText.length>0&&(i=s.innerText.replace("{0}",i)),u.textContent=i,u.innerText=i,t(u),n(e),n(o),c=="WL"&&r&&(r.style.className+=" sw_spd")):u&&e&&o&&(n(u),r&&n(r),t(e),t(o))};sj_evt.bind("fb:connected",i,1);sj_evt.bind("wl:auth",i,1);sj_evt.bind("fb:auth",i,1)}})()