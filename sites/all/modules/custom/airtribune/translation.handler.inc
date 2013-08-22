<?php

/**
 * @file Contains necessary translation handler overrides
 * @author Vadim Valuev<gease@mail.ru>
 */

/**
 * Class that attaches translation tab to profiles in case profile_page is on
 */
class AirtribuneTranslationDefaultHandler extends EntityTranslationDefaultHandler {

  protected function getPathInstance($path) {
    return parent::getPathInstance($path);
    return $this->entity->url();
  }
} 
