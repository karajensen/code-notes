/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QML MULTIMEDIA
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QtMultimedia.availableCameras
QtMultimedia.defaultCamera
QtMultimedia.convertVolume(volume, from, to)

------------------------------------------------------------------------------------------------------------
    
// CAMERA
// import QtMultimedia 5.8, Inherits QtObject
// Access viewfinder frames, and take photos and movies
Camera {
    availability
    cameraState
    cameraStatus
    captureMode
    deviceId
    digitalZoom
    displayName
    errorCode
    errorString
    lockStatus
    maximumDigitalZoom
    maximumOpticalZoom
    mediaObject
    metaData.cameraManufacturer
    metaData.cameraModel
    metaData.event
    metaData.subject
    metaData.orientation
    metaData.dateTimeOriginal
    metaData.gpsLatitude
    metaData.gpsLongitude
    metaData.gpsAltitude
    metaData.gpsTimestamp
    metaData.gpsTrack
    metaData.gpsSpeed
    metaData.gpsImgDirection
    metaData.gpsProcessingMethod
    opticalZoom
    orientation
    position
    viewfinder.resolution
    viewfinder.minimumFrameRate
    viewfinder.maximumFrameRate
    onCameraStateChanged: { state }
    onDigitalZoomChanged: { zoom }
    onError: { errorCode, errorString }
    onLockStatusChanged: {}
    onManualWhiteBalanceChanged: { qreal }
    onMaximumDigitalZoomChanged: { zoom }
    onMaximumOpticalZoomChanged: { zoom }
    onOpticalZoomChanged: { zoom }
    onWhiteBalanceModeChanged: { Camera::WhiteBalanceMode }
    
    // CameraCapture
    // Cannot be instantiated, only a child of Camera
    imageCapture {
        capturedImagePath
        errorString
        ready
        resolution
        supportedResolutions
        onCaptureFailed: { requestId, message }
        onImageCaptured: { requestId, preview }
        onImageMetadataAvailable: { requestId, key, valu }
        onImageSaved: { requestId, path }
    }
    
    // CameraExposure 
    // Cannot be instantiated, only a child of Camera
    exposure {
        aperture
        exposureCompensation
        exposureMode
        iso
        manualAperture
        manualIso 
        manualShutterSpeed
        meteringMode
        shutterSpeed
        spotMeteringPoint
        supportedExposureModes
    }
    
    // CameraFlash
    // Cannot be instantiated, only a child of Camera
    flash {
        mode
        ready
        supportedModes
    }
    
    // CameraFocus
    // Cannot be instantiated, only a child of Camera
    focus {
        customFocusPoint
        focusMode
        focusPointMode
        focusZones
        supportedFocusModes
        supportedFocusPointModes
    }
    
    // CameraImageProcessing 
    // Cannot be instantiated, only a child of Camera    
    imageProcessing {
        brightness
        colorFilter
        contrast
        denoisingLevel
        isAvailable
        manualWhiteBalance
        saturation
        sharpeningLevel
        supportedColorFilters
        supportedWhiteBalanceModes
        whiteBalanceMode
    }
    
    // CameraRecorder 
    // Cannot be instantiated, only a child of Camera    
    videoRecorder {
        actualLocation
        audioBitRate
        audioChannels
        audioCodec
        audioEncodingMode
        audioSampleRate
        duration
        errorCode 
        errorString
        frameRate
        mediaContainer
        muted
        outputLocation
        recorderState
        recorderStatus
        resolution
        videoBitRate 
        videoCodec
        videoEncodingMode
    }
}

camera.searchAndLock()
camera.start()
camera.stop()
camera.supportedViewfinderFrameRateRanges(resolution)
camera.supportedViewfinderResolutions(minimumFps, maximumFps)
camera.unlock()
    
camera.imageCapture.cancelCapture()
camera.imageCapture.capture()
camera.imageCapture.captureToLocation(location)
camera.imageCapture.setMetadata(key, value)
    
camera.exposure.setAutoAperture()
camera.exposure.setAutoIsoSensitivity()
camera.exposure.setAutoShutterSpeed()

camera.flash.flashModeChanged(int)
camera.flash.flashReady(bool)

camera.videoRecorder.record()
camera.videoRecorder.setMetadata(key, value)
camera.videoRecorder. stop()

------------------------------------------------------------------------------------------------------------

// MEDIAPLAYER
// import QtMultimedia 5.8
// Add media playback to a scene
MediaPlayer {
    audioRole
    autoLoad
    autoPlay
    availability
    bufferProgress
    customAudioRole
    duration
    error
    errorString
    hasAudio
    hasVideo
    loops
    mediaObject
    metaData.title
    metaData.subTitle
    metaData.author
    metaData.comment
    metaData.description
    metaData.category
    metaData.genre
    metaData.year
    metaData.date
    metaData.userRating
    metaData.keywords
    metaData.language
    metaData.publisher
    metaData.copyright
    metaData.parentalRating
    metaData.ratingOrganization
    metaData.size
    metaData.mediaType
    metaData.audioBitRate
    metaData.audioCodec
    metaData.averageLevel
    metaData.channelCount
    metaData.peakValue
    metaData.sampleRate
    metaData.albumTitle
    metaData.albumArtist
    metaData.contributingArtist
    metaData.composer
    metaData.conductor
    metaData.lyrics
    metaData.mood
    metaData.trackNumber
    metaData.trackCount
    metaData.coverArtUrlSmall
    metaData.coverArtUrlLarge
    metaData.resolution
    metaData.pixelAspectRatio
    metaData.videoFrameRate
    metaData.videoBitRate
    metaData.videoCodec
    metaData.posterUrl
    metaData.chapterNumber
    metaData.director
    metaData.leadPerformer 
    metaData.writer
    muted
    notifyInterval
    playbackRate
    playbackState
    playlist
    position
    seekable
    source
    status
    volume
    onError: { error, errorString }
    onPaused: {}
    onPlaybackStateChanged: {}
    onPlaying: {}
    onStopped: {}
}

player.pause()
playerplay()
playerseek(offset)
playerstop()
playersupportedAudioRoles()

------------------------------------------------------------------------------------------------------------

// VIDEO
// import QtMultimedia 5.8, Inherits Item
// A convenience type for showing a specified video
Video {
    audioRole
    autoLoad
    autoPlay
    availability
    bufferProgress
    customAudioRole
    duration
    error
    errorString
    fillMode
    hasAudio
    hasVideo
    loops
    metaData
    muted
    notifyInterval
    orientation
    playbackRate
    playbackState
    playlist
    position
    seekable
    source
    status
    volume
    onPaused()
    onPlaying()
    onStopped()    
}

video.pause()
video.play()
video.seek(offset)
video.stop()
video.supportedAudioRoles()

------------------------------------------------------------------------------------------------------------

// VIDEOOUTPUT
// import QtMultimedia 5.8
// Render video or camera viewfinder
VideoOutput {
    autoOrientation 
    contentRect
    fillMode
    filters
    orientation
    source
    sourceRect    
}

output.mapNormalizedPointToItem (point)
output.mapNormalizedRectToItem(rectangle)
output.mapPointToItem(point)
output.mapPointToSource(point)
output.mapPointToSourceNormalized(point)
output.mapRectToItem(rectangle)
output.mapRectToSource(rectangle)
output.mapRectToSourceNormalized(rectangle)

