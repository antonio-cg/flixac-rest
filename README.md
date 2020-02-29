# flixac-rest
iptv rest service to manage stream with nginx+rtmp+vod 

end points: 

Create stream:
/create/{stream-id}

Method: POST

body data:

{
	"url" :  "http:://example.url/to/reestream/.m3u8",
  "ffmpeg_command" : "-bsf:a aac_adtstoasc -acodec copy -vcodec copy -strict -2", <- extra command  to ffmpeg
	
  "created_by" : 1
}

stop:

/stop/{stream-id}

METHOD: GET

start:

/start/{stream-id}


TODO:

+Installation instructions 

+24/7 channels tranmistions from list of videos

+better error control from ffmpeg

+restart on trasnmition error or ffmpeg error

+restart transmition 

+user auth 

+log errors

+start all registered streams on startup

+cpu, ram, hdd usage information

+add vod from local or remote videos
