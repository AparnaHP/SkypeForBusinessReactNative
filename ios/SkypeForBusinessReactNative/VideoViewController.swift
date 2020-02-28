//+----------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// Module name: VideoViewController.swift
//----------------------------------------------------------------


import UIKit
import GLKit

/**
 *  VideoViewController handles AV chat using Skype for Business SDK.
 *  Namely, it uses a convenient helper SfBConversationHelper.h included in the
 *  Helpers folder of the SDK.
 */

class VideoViewController: UIViewController,SfBConversationHelperDelegate,SfBAlertDelegate
{
   
   
    @IBOutlet weak var speakerButton: UIButton!
    @IBOutlet weak var toggleVideo: UIButton!
    @IBOutlet weak var participantVideoView: GLKView!
    @IBOutlet weak var selfVideoView: UIView!
    @IBOutlet weak var muteButton: UIButton!
    @IBOutlet weak var endCallButton: UIButton!
    @IBOutlet weak var videoButton: UIButton!
    @IBOutlet weak var activityIndicator: UIActivityIndicatorView!
    @IBOutlet weak var connectingCamLabel: UILabel!
    
    var conversationInstance:SfBConversation? = nil
    var deviceManagerInstance: SfBDevicesManager? = nil
    var conversationHelper:SfBConversationHelper? = nil
  
    let DisplayNameInfo:String = "displayName"
    let isDefaultOptionsOn = ObjCBool(true)

    var startedCall = false
    var startedAudio = 0
    var startedVideo = 0

    var displayName: String? = nil
    fileprivate var sfb: SfBApplication?

    required init?(coder aDecoder: NSCoder) {
        super.init(coder: aDecoder)
        self.registerForAppTerminationNotification()
    }

    
    override func viewDidLoad() {
        super.viewDidLoad()
        self.navigationItem.setHidesBackButton(true, animated: true)
        self.toggleVideo.layer.zPosition = .greatestFiniteMagnitude
      
        #if targetEnvironment(simulator)
          self.showSimulatorAlert()
        #else
          self.initializeSkype()
        #endif
    }

    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    override func viewWillAppear(_ animated: Bool) {
        self.navigationController?.setNavigationBarHidden(true, animated: false)
      
        let statusBar: UIView = UIApplication.shared.value(forKey: "statusBar") as! UIView
        if statusBar.responds(to:#selector(setter: UIView.backgroundColor)) {
          statusBar.backgroundColor = UIColor.white
        }
    }
    
    /**
     *  Initialize UI.
     *  Bring information bar from bottom to the visible area of the screen.
     */
  
    deinit {
      
        NotificationCenter.default.removeObserver(self)
    }
  
    func initializeSkype(){
      sfb = SfBApplication.shared()
      if let sfb = sfb{
        sfb.configurationManager.maxVideoChannels = 1
        sfb.configurationManager.requireWifiForAudio = false
        sfb.configurationManager.requireWifiForVideo = false
        sfb.configurationManager.enablePreviewFeatures = true
        sfb.alertDelegate = self
      }
      
      
      if let sfb = sfb{
        let config = sfb.configurationManager
        config.setEndUserAcceptedVideoLicense()
        if(didJoinMeeting()){
          self.joinMeeting()
        }
      }
      
    }
  
    func showSimulatorAlert()
    {
      let alert = UIAlertController(title: NSLocalizedString("Alert", comment: ""), message: NSLocalizedString("Not_Supported", comment: ""), preferredStyle: .alert)
      alert.addAction(UIAlertAction(title: NSLocalizedString("Cancel", comment: ""), style: .cancel, handler: { action in
        self.dismiss(animated: true, completion: nil)
      }))
      self.present(alert, animated: true, completion: nil)
    }
  
    func didJoinMeeting() -> Bool {
      
      let meetingURLString:String = getMeetingURLString
      let meetingDisplayName:String = getMeetingDisplayName
      
      do {
        let urlText:String = meetingURLString.addingPercentEncoding(withAllowedCharacters: CharacterSet.urlQueryAllowed)!
        let url = URL(string:urlText)
        
        deviceManagerInstance=sfb!.devicesManager
        conversationInstance = try sfb!.joinMeetingAnonymous(withUri: url!, displayName: meetingDisplayName).conversation
        displayName = getMeetingDisplayName
        
        return true
      }
      catch  {
        //print("ERROR! Joining online meeting>\(error)")
        showErrorAlert(NSLocalizedString("Fail_Online_Meeting", comment: ""), viewController: self)
        return false
      }
      
    }
    /**
     *  Initialize UI.
     *  Bring information bar from bottom to the visible area of the screen.
     */

    
    /**
     *  Joins a Skype meeting.
     */
    func joinMeeting() {
        
        conversationInstance!.alertDelegate = self
        

        self.conversationHelper = SfBConversationHelper(conversation: conversationInstance!,
                                                        delegate: self,
                                                        devicesManager: deviceManagerInstance!,
                                                        outgoingVideoView: self.selfVideoView,
                                                        incomingVideoLayer: self.participantVideoView.layer as! CAEAGLLayer,
                                                        userInfo: [DisplayNameInfo:displayName!])
        
        conversationInstance!.addObserver(self, forKeyPath: "canLeave", options: .initial , context: nil)
  
      
        self.endCallButton.isEnabled = false
        self.muteButton.isHidden = true
        self.speakerButton.isHidden = true
        self.videoButton.isHidden = true

    }
    
    //MARK: User Button Actions
    
    
    @IBAction func endCall(_ sender: AnyObject) {
        
        // Get conversation handle and call leave.
        // Need to check for canLeave property of conversation,
        // in this case happens in KVO
        if let conversation = self.conversationHelper?.conversation{
            if(!leaveMeetingWithSuccess(conversation)){
                
                showErrorAlert(NSLocalizedString("Cannot_Leave", comment: ""), viewController: self)
            }
            stopVideoService();
            self.conversationHelper?.conversation.removeObserver(self, forKeyPath: "canLeave")
        }
      
      self.dismiss(animated: true, completion: nil)
      
}

   
    
    @IBAction func toggleMute(_ sender: AnyObject) {
        do{
          if(self.conversationHelper?.conversation.audioService.canToggleMute ?? false)
          {
            try self.conversationHelper?.conversation.audioService.toggleMute()
          }
        }
        catch let error as NSError {
             print(error.localizedDescription)
            //self.handleError("Could Not Perform The Audio Action!")
        }
    }
    
    
    @IBAction func toggleVideoOn(_ sender: Any)
    {
        do{
          
          if(startedCall)
          {
            try self.conversationHelper?.toggleVideoPaused()
          }
          else
          {
            startVideoService()
          }
        }
        catch let error as NSError {
            print(error.localizedDescription)
            //self.handleError("Could Not Perform The Video Action!")
        }
        
    }
  
    
    @IBAction func switchCamera(_ sender: Any)
    {
        do{
            try self.conversationHelper?.changeActiveCamera()
        }
        catch let error as NSError {
            print(error.localizedDescription)
            //self.handleError("Could Not Perform The Video Action!")
        }
    }
    
    @IBAction func speakerChange(_ sender: Any)
    {
      self.conversationHelper?.changeSpeakerEndpoint()
    }
  
    //MARK - Skype SfBConversationHelperDelegate Functions
    
    // At incoming video, unhide the participant video view
    
    func conversationHelper(_ conversationHelper: SfBConversationHelper, didSubscribeTo video: SfBParticipantVideo?) {
      
        if(video?.isPaused ?? true)
        {
          self.participantVideoView.isHidden = true
        }
        else
        {
          self.participantVideoView.isHidden = false
        }
    }
  
    func startVideoService()
    {
      do
      {
        self.videoButton.setImage(UIImage(named: "unmuting.png"), for: UIControl.State.normal)

        if(self.conversationHelper?.conversation.videoService.canStart ?? false)
        {
          try self.conversationHelper?.conversation.videoService.start()
          self.startedCall=true
        }
        else
        {
          stopVideoService()
          self.videoButton.setImage(UIImage(named: "unmuting.png"), for: UIControl.State.normal)
          DispatchQueue.main.asyncAfter(deadline: .now() + 3.0, execute:
          {
              self.videoButton.sendActions(for: .touchUpInside)
          })
        }
      }
      catch let error as NSError {
        print(error.localizedDescription)
        self.startedCall=false
        self.videoButton.setImage(UIImage(named: "videooff.png"), for: UIControl.State.normal)
      }
    }
  
    func stopVideoService()
    {
      do
      {
        if(self.conversationHelper?.conversation.videoService.canStop ?? false)
        {
          try self.conversationHelper?.conversation.videoService.stop()
          
        }
      }
      catch let error as NSError {
        print(error.localizedDescription)
      }
    }
  
    // When video service is ready to start, unhide self video view and start the service.
    func conversationHelper(_ conversationHelper: SfBConversationHelper, videoService: SfBVideoService, didChangeCanStart canStart: Bool) {
      
       /*do
       {
       /*if(videoService.canStart
       {
       try videoService.start()
       }*/
       
       }
       catch let error as NSError {
       print(error.localizedDescription)
       }*/
      
    }

  
    // When the audio status changes, reflect in UI
    func conversationHelper(_ conversationHelper: SfBConversationHelper, audioService: SfBAudioService, didChangeMuted muted: SfBAudioServiceMuteState) {
      
        if muted == .muted //1
        {
            if(startedAudio == 0 && isDefaultOptionsOn.boolValue)
            {
              startedAudio = 1
              self.muteButton.setImage(UIImage(named: "mute.png"), for: UIControl.State.normal)
              DispatchQueue.main.asyncAfter(deadline: .now() + 3.0, execute:
              {
                
                  self.stopLoading()
                  self.muteButton.sendActions(for: .touchUpInside)
                  self.speakerButton.sendActions(for: .touchUpInside)
                
                  self.startCameraNotify()

              })

            }
            else if(startedAudio == 0 && !isDefaultOptionsOn.boolValue)
            {
              startedAudio = 1
              self.muteButton.setImage(UIImage(named: "mute.png"), for: UIControl.State.normal)
              self.stopLoading()
            }
            else
            {
              self.muteButton.setImage(UIImage(named: "mute.png"), for: UIControl.State.normal)
            }

        }
        else if muted == .unmuting //2
        {
            self.muteButton.setImage(UIImage(named: "unmuting.png"), for: UIControl.State.normal)
        }
        else if muted == .unmuted //0
        {
            if(startedAudio == 0)
            {
              self.muteButton.setImage(UIImage(named: "mute.png"), for: UIControl.State.normal)
            }
            else
            {
              self.muteButton.setImage(UIImage(named: "unmute.png"), for: UIControl.State.normal)
            }
        }
        else
        {
            self.muteButton.setImage(UIImage(named: "unmuting.png"), for: UIControl.State.normal)
        }
    }
    
    func conversationHelper(_ conversationHelper: SfBConversationHelper, videoService: SfBVideoService, didChangeActiveCamera activeCamera: SfBCamera)
    {

            if(self.conversationHelper?.conversation.videoService.canSetActiveCamera ?? false)
            {
                self.videoButton.setImage(UIImage(named: "videoon.png"), for: UIControl.State.normal)
                self.selfVideoView.isHidden = false
                if(startedCall && isDefaultOptionsOn.boolValue && startedVideo==0)
                {
                  startedVideo=1;
                  
                  stopCameraNotify()
                }
            }
            else
            {
                self.videoButton.setImage(UIImage(named: "videooff.png"), for: UIControl.State.normal)
                self.selfVideoView.isHidden = true
            }

    }
    
    func conversationHelper(_ conversationHelper: SfBConversationHelper, conversation: SfBConversation, didChange changedState: SfBConversationState)
    {

        if(self.conversationHelper?.conversation.state == SfBConversationState.established)
        {
           //add what you want to do after establishing...
        }
    }
  
  func stopLoading()
  {
    self.activityIndicator.stopAnimating()
    self.endCallButton.isEnabled = true
    self.muteButton.isHidden = false
    self.speakerButton.isHidden = false
    self.videoButton.isHidden = false

  }
  
  func startCameraNotify()
  {
    self.videoButton.sendActions(for: .touchUpInside)
    self.videoButton.isEnabled = false
    self.connectingCamLabel.isHidden=false
    self.connectingCamLabel.text = NSLocalizedString("Connect_Camera", comment: "")
  }
  
  func stopCameraNotify()
  {
    self.videoButton.isEnabled = true
    self.connectingCamLabel.isHidden=true
  }
  
  func conversationHelper(_ conversationHelper: SfBConversationHelper, speaker: SfBSpeaker, didChangeActiveEndpoint changedEndPoint: SfBSpeakerEndpoint)
  {
      switch (speaker.activeEndpoint)
      {
          case SfBSpeakerEndpoint.loudspeaker:
            self.speakerButton.setImage(UIImage(named: "speakeron.png"), for: UIControl.State.normal)
            break;
          case SfBSpeakerEndpoint.nonLoudspeaker:
            self.speakerButton.setImage(UIImage(named: "speakeroff.png"), for: UIControl.State.normal)
            break;
      }
  }


   //MARK: - Additional KVO

    
    // Monitor canLeave property of a conversation to prevent leaving prematurely
    override func observeValue(forKeyPath keyPath: String?, of object: Any?, change: [NSKeyValueChangeKey : Any]?, context: UnsafeMutableRawPointer?) {
      
         if (keyPath == "canLeave")
         {
         self.endCallButton.isEnabled = (self.conversationHelper?.conversation.canLeave)!
         }
    }
    
    func registerForAppTerminationNotification() {
        
        NotificationCenter.default.addObserver(self, selector:#selector(VideoViewController.leaveMeetingWhenAppTerminates(_:)), name:UIApplication.willTerminateNotification, object:nil)
    }
    
    
    @objc func leaveMeetingWhenAppTerminates(_ aNotification:Notification) {
        if let conversation = conversationHelper?.conversation{
            _ = leaveMeetingWithSuccess(conversation)
        }
    }

    
    //MARK: - Helper UI
    
    func handleError(_ readableErrorDescription:String)  {
        let alertController:UIAlertController = UIAlertController(title: "ERROR!", message: readableErrorDescription, preferredStyle: .alert)
        
        alertController.addAction(UIAlertAction(title: "Close", style: .cancel, handler: nil))
        present(alertController, animated: true, completion:nil)
    }
   
    
    func didReceive(_ alert: SfBAlert) {
       alert.showSfBAlertInController(self)
    }
  
}
