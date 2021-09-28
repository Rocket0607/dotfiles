(require 'package)
(add-to-list 'package-archives
             '("melpa" . "https://melpa.org/packages/"))
(package-refresh-contents)
(package-initialize)

(unless (package-installed-p 'use-package)
(package-install 'use-package))
(require 'use-package-ensure)
(setq use-package-always-ensure t)

(add-to-list 'load-path "~/.rocket.d/load_path/")

(use-package evil
:init      ;; tweak evil's configuration before loading it
(setq evil-want-integration t) ;; This is optional since it's already set to t by default.
(setq evil-want-keybinding nil)
(setq evil-vsplit-window-right t)
(setq evil-split-window-below t)
(evil-mode))
(use-package evil-collection
:after evil
:config
(setq evil-collection-mode-list '(dashboard dired ibuffer))
(evil-collection-init))

(use-package undo-tree)
(global-undo-tree-mode)
(setq evil-undo-system 'undo-tree)

(use-package benchmark-init
  :ensure t
  :config
  ;; To disable collection of benchmark data after init is done.
  (add-hook 'after-init-hook 'benchmark-init/deactivate))

(use-package general
   :config (general-evil-setup t))

(nvmap :states '(normal visual) :keymaps 'override :prefix "SPC"
  "SPC"   '(execute-extended-command :which-key "M-x")
  "."     '(find-file :which-key "Find file")
  "h r r" '((lambda () (interactive) (load-file "~/.rocket.d/init.el")) :which-key "Reload emacs config")
  "t t"   '(toggle-truncate-lines :which-key "Toggle truncate lines"))

(nvmap :prefix "SPC"
  "b b"   '(ibuffer :which-key "Ibuffer")
  "b s"   '(switch-to-buffer :which-key "Ibuffer")
  "b c"   '(clone-indirect-buffer-other-window :which-key "Clone indirect buffer other window")
  "b k"   '(kill-current-buffer :which-key "Kill current buffer")
  "b n"   '(next-buffer :which-key "Next buffer")
  "b p"   '(previous-buffer :which-key "Previous buffer")
  "b B"   '(ibuffer-list-buffers :which-key "Ibuffer list buffers")
  "b f"   '(lsp-format-buffer :which-key "format buffer using LSP")
  "b K"   '(kill-buffer :which-key "Kill buffer"))

(nvmap :prefix "SPC"
  ;; Window splits
  "w c"   '(evil-window-delete :which-key "Close window")
  "w n"   '(evil-window-new :which-key "New window")
  "w s"   '(evil-window-split :which-key "Horizontal split window")
  "w v"   '(evil-window-vsplit :which-key "Vertical split window")
  ;; Window motions
  "w h"   '(evil-window-left :which-key "Window left")
  "w j"   '(evil-window-down :which-key "Window down")
  "w k"   '(evil-window-up :which-key "Window up")
  "w l"   '(evil-window-right :which-key "Window right")
  "w w"   '(evil-window-next :which-key "Goto next window"))

;; function that sends an r to a buffer named "vterm-flutter", which reloads when flutter run is being run.
(defun flutter-reload () (interactive) (progn (set-buffer "vterm-flutter") (term-send-raw-string "r\n")))
(nvmap :prefix "SPC"
  "r"   '(flutter-reload :which-key "reload flutter when flutter run is being run in vterm"))

(nvmap :prefix "SPC"
  "o t"   '(vterm :which-key "Open vterm"))

(use-package doom-themes)
(setq doom-themes-enable-bold t    ; if nil, bold is universally disabled
   doom-themes-enable-italic t) ; if nil, italics is universally disabled
(load-theme 'doom-one t)

(set-face-attribute 'default nil
	:font "Jetbrains Mono"
	:height 145
	:weight 'medium)
	(set-face-attribute 'variable-pitch nil
	:font "Ubuntu Mono Nerd Font"
	:height 155
	:weight 'medium)
	(set-face-attribute 'fixed-pitch nil
	:font "Jetbrains Mono"
	:height 145
	:weight 'medium)
	;; Makes commented text and keywords italics.
	;; This is working in emacsclient but not emacs.
	;; Your font must have an italic face available.
	(set-face-attribute 'font-lock-comment-face nil
	:slant 'italic)
	(set-face-attribute 'font-lock-keyword-face nil
	:slant 'italic)

	;; Uncomment the following line if line spacing needs adjusting.
	;;(setq-default line-spacing 0.12)

	;; changes certain keywords to symbols, such as lamda!
	(setq global-prettify-symbols-mode t)

(defconst jetbrains-ligature-mode--ligatures
	 '("->" "<-" "<=>" "==" "!=" "<=" ">=" "=:=" "!==" "===" "++" "=>"))

(sort jetbrains-ligature-mode--ligatures (lambda (x y) (> (length x) (length y))))

(dolist (pat jetbrains-ligature-mode--ligatures)
	(set-char-table-range composition-function-table
											(aref pat 0)
											(nconc (char-table-range composition-function-table (aref pat 0))
														 (list (vector (regexp-quote pat)
																					 0
																		'compose-gstring-for-graphic)))))

(global-set-key (kbd "C-=") 'text-scale-increase)
(global-set-key (kbd "C--") 'text-scale-decrease)
(global-set-key (kbd "<C-wheel-up>") 'text-scale-increase)
(global-set-key (kbd "<C-wheel-down>") 'text-scale-decrease)

(use-package all-the-icons)

(menu-bar-mode -1)
(tool-bar-mode -1)
(scroll-bar-mode -1)

(global-display-line-numbers-mode 1)
(global-visual-line-mode t)

(use-package doom-modeline)
(doom-modeline-mode 1)

(setq scroll-conservatively 101) ;; value greater than 100 gets rid of half page jumping
(setq mouse-wheel-scroll-amount '(3 ((shift) . 3))) ;; how many lines at a time
(setq mouse-wheel-progressive-speed t) ;; accelerate scrolling
(setq mouse-wheel-follow-mouse 't) ;; scroll window under mouse

(use-package highlight-indent-guides
:commands highlight-indent-guides-mode
:hook (prog-mode . highlight-indent-guides-mode)
:config
(setq highlight-indent-guides-method 'character
	highlight-indent-guides-character ?>
	highlight-indent-guides-delay 0.01
	highlight-indent-guides-responsibe 'top
	highlight-indent-guides-auto-enabled nil))

(use-package dashboard
  :init      ;; tweak dashboard config before loading it
  (setq dashboard-set-heading-icons t)
  (setq dashboard-set-file-icons t)
  (setq dashboard-banner-logo-title "Rocket Emacs")
  (setq dashboard-startup-banner 'logo) ;; use standard emacs logo as banner
  ;;(setq dashboard-startup-banner "/home/dt/.emacs.d/emacs-dash.png")  ;; use custom image as banner
  (setq dashboard-center-content nil) ;; set to 't' for centered content
  (setq dashboard-items '((recents . 10)
                          (agenda . 10)))
  :config
  (dashboard-setup-startup-hook)
  (dashboard-modify-heading-icons '((recents . "file-text")
			      (bookmarks . "book"))))

(setq initial-buffer-choice (lambda () (get-buffer "*dashboard*")))

(use-package vertico
  :bind (:map vertico-map
	 ("M-j" . vertico-next)
	 ("M-k" . vertico-previous)
	 ("C-f" . vertico-exit)
	 :map minibuffer-local-map
	 ("M-h" . backward-kill-word))
  :custom
  (vertico-cycle t)
  :init
  (vertico-mode))

(use-package savehist
  :init
  (savehist-mode))

(use-package marginalia
  :after vertico
  :custom
  (marginalia-annotators '(marginalia-annotators-heavy marginalia-annotators-light nil))
  :init
  (marginalia-mode))

(use-package company)

(use-package which-key)
(which-key-mode)

(use-package elfeed
	:config
	(setq elfeed-search-feed-face ":foreground #fff :weight bold")
	(setq elfeed-feeds '(
		("https://www.linuxjournal.com/node/feed" linux linuxjournal articles)
		("https://www.reddit.com/r/emacs.rss" linux emacs reddit)
    ("https://hackaday.com/blog/feed/" hackaday linux)
		("https://opensource.com/feed" opensource linux)
		("https://linux.softpedia.com/backend.xml" softpedia linux)
		("https://itsfoss.com/feed/" itsfoss linux)
		("https://www.phoronix.com/rss.php" phoronix linux)
		("https://www.computerworld.com/index.rss" computerworld linux)
		("https://www.techrepublic.com/rssfeeds/topic/open-source/" techrepublic linux)
		("https://betanews.com/feed" betanews linux)
                ("https://reddit.com/r/linuxmasterrace.rss" memes linux reddit)
"https://rss.nytimes.com/services/xml/rss/nyt/Technology.xml"
		("http://lxer.com/module/newswire/headlines.rss" lxer linux))))

 (use-package elfeed-goodies
	 :init
	 (elfeed-goodies/setup)
	 :config
	 (setq elfeed-goodies/entry-pane-size 0.5))

 (add-hook 'elfeed-show-mode-hook 'visual-line-mode)
 (evil-define-key 'normal elfeed-show-mode-map
	 (kbd "J") 'elfeed-goodies/split-show-next
	 (kbd "K") 'elfeed-goodies/split-show-prev)
 (evil-define-key 'normal elfeed-search-mode-map
	 (kbd "J") 'elfeed-goodies/split-show-next
	 (kbd "K") 'elfeed-goodies/split-show-prev)
 (evil-define-key 'normal elfeed-search-mode-map
	 (kbd "RET") 'elfeed-goodies/split-search-show-entry)
 (evil-define-key 'normal elfeed-search-mode-map 
   (kbd "SPC r") 'elfeed-show-visit)

(use-package lsp-mode
:defer t
	 :bind ("C-l" . lsp-mode)
						)

(use-package lsp-ui)

(use-package lsp-dart
:hook (dart-mode . lsp)
:config
(setq lsp-dart-sdk-dir "/home/rohitk/snap/flutter/common/flutter/bin/cache/dart-sdk/")
(setq lsp-enable-links nil))



(use-package web-mode)
(add-to-list 'auto-mode-alist '("\\.ts\\'" . web-mode))
(add-to-list 'auto-mode-alist '("\\.html?\\'" . web-mode))
(add-to-list 'auto-mode-alist '("\\.css?\\'" . web-mode))
(add-to-list 'auto-mode-alist '("\\.js\\'" . web-mode))

(defun my-web-mode-hook ()
  "Hooks for Web mode."
  (setq web-mode-markup-indent-offset 2)
  (setq web-mode-code-indent-offset 2)
  (setq web-mode-css-indent-offset 2)
)
(add-hook 'web-mode-hook  'my-web-mode-hook)    
(setq tab-width 2)

(setq web-mode-enable-current-column-highlight t)
(setq web-mode-enable-current-element-highlight t)

(use-package emmet-mode)
(add-hook 'web-mode-hook  'emmet-mode) 
(add-hook 'web-mode-before-auto-complete-hooks
		'(lambda ()
		       (let ((web-mode-cur-language
				(web-mode-language-at-pos)))
							       (if (string= web-mode-cur-language "php")
				       (yas-activate-extra-mode 'php-mode)
				       (yas-deactivate-extra-mode 'php-mode))
							       (if (string= web-mode-cur-language "css")
				       (setq emmet-use-css-transform t)
				       (setq emmet-use-css-transform nil)))))

(use-package haskell-mode)

(defun my-asm-mode-hook ()
;; you can use `comment-dwim' (M-;) for this kind of behaviour anyway
(local-unset-key (vector asm-comment-char))
;; asm-mode sets it locally to nil, to "stay closer to the old TAB behaviour".
(setq tab-always-indent (default-value 'tab-always-indent))
(setq tab-stop-list (number-sequence 0 60 2)))

(add-hook 'asm-mode-hook #'my-asm-mode-hook)

(use-package lsp-python-ms
  :ensure t
  :init (setq lsp-python-ms-auto-install-server t)
  :hook (python-mode . (lambda ()
                          (require 'lsp-python-ms)
                          (lsp))))  ; or lsp-deferred

(add-hook 'c++-mode-hook 'lsp)
   (add-hook 'c-mode-hook 'lsp)
(setq lsp-clients-clangd-args '(
                                  ;; If set to true, code completion will include index symbols that are not defined in the scopes
                                  ;; (e.g. namespaces) visible from the code completion point. Such completions can insert scope qualifiers
                                  "--all-scopes-completion"
                                  ;; Index project code in the background and persist index on disk.
                                  "--background-index"
                                  ;; Enable clang-tidy diagnostics
                                  "--clang-tidy"
                                  ;; Whether the clang-parser is used for code-completion
                                  ;;   Use text-based completion if the parser is not ready (auto)
                                  "--completion-parse=auto"
                                  ;; Granularity of code completion suggestions
                                  ;;   One completion item for each semantically distinct completion, with full type information (detailed)
                                  "--completion-style=detailed"
                                  ;; clang-format style to apply by default when no .clang-format file is found
                                  "--fallback-style=Chromium"
                                  ;; When disabled, completions contain only parentheses for function calls.
                                  ;; When enabled, completions also contain placeholders for method parameters
                                  "--function-arg-placeholders"
                                  ;; Add #include directives when accepting code completions
                                  ;;   Include what you use. Insert the owning header for top-level symbols, unless the
                                  ;;   header is already directly included or the symbol is forward-declared
                                  "--header-insertion=iwyu"
                                  ;; Prepend a circular dot or space before the completion label, depending on whether an include line will be inserted or not
                                  "--header-insertion-decorators"
                                  ;; Enable index-based features. By default, clangd maintains an index built from symbols in opened files.
                                  ;; Global index support needs to enabled separatedly
                                  "--index"
                                  ;; Attempts to fix diagnostic errors caused by missing includes using index
                                  "--suggest-missing-includes"
                                  ;; Number of async workers used by clangd. Background index also uses this many workers.
                                  "-j=4"
                                  ))

(setq org-directory "~/Documents/org/")

(setq org-src-fontify-natively t
    org-src-tab-acts-natively t
    org-confirm-babel-evaluate nil
    org-edit-src-content-indentation 0)

(use-package projectile
  :config
  (projectile-global-mode 1))

(setq projectile-project-search-path '("~/Documents/"))

(use-package vterm)
